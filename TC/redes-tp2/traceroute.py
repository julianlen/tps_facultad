#! /usr/bin/env python
import logging
logging.getLogger("scapy.runtime").setLevel(logging.ERROR)

from geoip import geolite2
from scapy.all import *
import argparse
import time
import json
import signal
import ipaddress
import sys
import pylab
import matplotlib.pyplot as plt
import copy
from socket import getaddrinfo
import numpy
from scipy import stats
from math import sqrt, pow
import urllib

from io import BytesIO
from PIL import Image
from io import StringIO

# Predefined hosts
AUSTRALIA = 'sydney.edu.au'
JAPAN = 'www.u-tokyo.ac.jp'
INDIA = 'mhrd.gov.in'
ICELAND = 'english.hi.is'

# Constants
TIME_EXCEEDED_TYPE = 11
MAX_HOPS = 50
MAX_TIMEDOUTS = 5
PACKAGES_BURST = 40
TIMEOUT = 3
REACHED_END_CONDITION = False

def trace(hostToTrace, getGraphs, getMap, getJSON):
    print('\nHost: ' + str(hostToTrace) + '\n')
    tracedRoute = traceTheRoute(hostToTrace, PACKAGES_BURST)
    outliers, tau = anyJumps(tracedRoute)

    for route in tracedRoute:
        for outlier in outliers:
            if outlier['dstIp'] == route['ip_address']:
                route['salto_intercontinental'] = True
    if getGraphs:
        generateGraphs(copy.copy(tracedRoute), tau)

    if getMap:
        generateMap(copy.copy(tracedRoute))
        generateCimbalaMap(copy.copy(outliers))

    if getJSON:
        print('\n')
        print(json.dumps(tracedRoute, indent = 4, separators =(',', ': ')))
        fileName = hostToTrace + '.json'
        print('Converting JSON to ' + fileName)
        with open(fileName, 'wa') as traceFile:
            json.dump(tracedRoute, traceFile, indent = 4, separators =(',', ': '))

def tryGeolocalization(ipAddress):
    match = geolite2.lookup(ipAddress)
    country = ""
    continent = ""
    location = ""
    # Try geolocalization
    if match is not None:
        country = match.country
        continent = match.continent
        location = match.location

    return (country, continent, location)
            
def traceTheRoute(host, totalPackages):
    steps = []
    lastValidStep = 1

    for step in range(1, MAX_HOPS + 1):
        if REACHED_END_CONDITION:
            break

        # Send ICMP burst
        rttMean, ipAddress, pctNotSent = sendICMP(host, totalPackages, step)
        # When not timed out
        if (0 < rttMean and rttMean < TIMEOUT):
            (country, continent, location) = tryGeolocalization(ipAddress)
            
            steps.append({
                'rtt' : rttMean, 
                'ip_address' : ipAddress, 
                'salto_intercontinental' : False, 
                'hop_num' : step, 
                'pctNotSent' : pctNotSent, 
                'country' : country, 
                'continent' : continent,
                'location' : location,
                'isIpPrivate' : True if isPrivateIP(ipAddress) else False
            })
        # When timed out
        else:
            steps.append({
                'rtt' : None, 
                'ip_address' : None, 
                'salto_intercontinental' : None, 
                'hop_num' : step, 
                'pctNotSent' : 100, 
                'country' : None, 
                'continent' : None,
                'location' : None,
                'isIpPrivate' : None
            })
    return steps

def sendICMP(host, totalPackages, ttl):
    rttMean = 0
    packagesSent = 0
    global REACHED_END_CONDITION
    timedoutPackets = 0
    ipAddress = None

    for i in range(0, totalPackages):
        # Create the ICMP packet
        ttlStr = '[TTL #'  + str(ttl) + '] '
        print(ttlStr + 'about to send ' + str(i) +' to ' + str(host))
        pkt = IP(dst=host, ttl=ttl) / ICMP()
        start = time.time()

        # Send the packet and get a reply
        reply = sr1(pkt, verbose=0, timeout=TIMEOUT)
        rtt = time.time() - start

        # If timeouts surpass the threshold then stop
        if rtt >= TIMEOUT:
            print(ttlStr + 'packet ' + str(i) + ' timed-out')
            timedoutPackets += 1
            if timedoutPackets >= MAX_TIMEDOUTS:
                break
            continue
        
        # If the reply is a valid ICMP package
        if not reply is None:
            print(ttlStr + 'sent and received packet ' + str(i) + ' coming from ' + str(reply.src))
            ipAddress = reply.src
            timedoutPackets = 0
            rttMean += rtt
            packagesSent += 1

            # TTL was not enough to reach destination
            if reply.type == TIME_EXCEEDED_TYPE:
                print(ttlStr + 'reply type is time exceeded')
            # Destination was reached
            else:
                print(ttlStr + 'host was reached')
                REACHED_END_CONDITION = True

    rttMean /= packagesSent if packagesSent > 0 else 1
    pctNotSent = 100 - (packagesSent * 100 / totalPackages)
    return rttMean, ipAddress, pctNotSent

# Detects private IPs
def isPrivateIP(ip):
    priv_lo = re.compile("^127\.\d{1,3}\.\d{1,3}\.\d{1,3}$")
    priv_24 = re.compile("^10\.\d{1,3}\.\d{1,3}\.\d{1,3}$")
    priv_20 = re.compile("^192\.168\.\d{1,3}.\d{1,3}$")
    priv_16 = re.compile("^172.(1[6-9]|2[0-9]|3[0-1]).[0-9]{1,3}.[0-9]{1,3}$")
    return priv_lo.match(ip) or priv_24.match(ip) or priv_20.match(ip) or priv_16.match(ip)

def anyJumps(tracedRoute):
    print('\nSaltos Intercontinentales:\n')
    dataSteps, meanSteps = calculateMeanDiff(tracedRoute)

    jumps, tau = intercontinentalJumps(meanSteps)
    print(json.dumps(jumps, indent = 4, separators =(',', ': ')))
    print("Saltos totales: {}").format(dataSteps[0]['totalHops'])
    print("Cantidad de timeouts: {}".format(dataSteps[0]['timeOuts']))
    print("Cantidad de RTT negativos: {}".format(dataSteps[0]['negativeRTT']))
    print("Cantidad de IP's privadas: {}".format(dataSteps[0]['privatesIP']))
    return jumps, tau

def calculateMeanDiff(tracedRoute):
    meanSteps = []
    dataSteps = []
    lastMean = 0
    privatesIP = 0
    deltaMeanNegative = 0
    timeOuts = 0
    totalHops = 0
    ip_src = ""
    ip_src_isPrivate = True

    # Order the traced routes list by hop_num and calculate differences
    for route in sorted(tracedRoute, key=lambda obj: int(obj['hop_num'])):
        ip_dest = route['ip_address']
        ip_dest_isPrivate = route['isIpPrivate']
        totalHops += 1

        if route['rtt'] is None:
            timeOuts += 1
        else:
            deltaMean = route['rtt'] - lastMean
            lastMean = route['rtt']
            if deltaMean <= 0:
                deltaMeanNegative += 1
            if route['isIpPrivate']:
                privatesIP += 1
            # Filter private ips and negative deltas
            if deltaMean > 0 and not route['isIpPrivate']:
                (country_src, continent_src, location_src) = tryGeolocalization(ip_src)
                (country_dst, continent_dst, location_dst) = tryGeolocalization(ip_dest)

                meanSteps.append({
                    'srcIp' : ip_src,
                    'srcCountry' : country_src,
                    'srcContinent' : continent_src,
                    'srcLocation' : location_src,
                    'srcIpIsPrivate' : ip_src_isPrivate,
                    'dstIp' : ip_dest, 
                    'dstCountry' : country_dst,
                    'dstContinent' : continent_dst,
                    'dstLocation' : location_dst,
                    'dstIpIsPrivate' : ip_dest_isPrivate,
                    'deltaMean' : deltaMean, 
                    'step' : route['hop_num']
                })
            ip_src = ip_dest
            ip_src_isPrivate = ip_dest_isPrivate

    dataSteps.append({
        'timeOuts' : timeOuts, 
        'negativeRTT' : deltaMeanNegative, 
        'privatesIP' : privatesIP,
        'totalHops' : totalHops
    })
    return dataSteps, meanSteps

# Recibe array de (ip, deltaMean), devuelve array de (ip, maxMean)
def intercontinentalJumps(meanSteps):
    outliers = []
    normals = list(meanSteps)

    # Tau requires at least 3 elements
    finishedPrediction = len(normals) < 3

    while not finishedPrediction:
        n = len(normals)
        sample = numpy.array([step['deltaMean'] for step in normals])
        X = numpy.mean(sample)
        S = numpy.std(sample)
        t = stats.t.ppf(1 - 0.025, n - 2)
        tau = (t * (n - 1)) / (sqrt(n) * sqrt((n - 2) + pow(t, 2)))
        tauS = tau * S
        maxStep = max(normals, key=lambda obj: obj['deltaMean'])

        #maxSrc, maxMean, maxHop = max(normals, key=lambda i: i[1])
        if n > 3 and abs(maxStep['deltaMean'] - X) > tauS:
            outliers.append(maxStep)
            normals = [step for step in normals if not maxStep['dstIp'] == step['dstIp']]
        else:
            finishedPrediction = True
    return outliers, tau

def generateGraphs(tracedRoute, tau):
    x_saltos = []
    rttEntreSalto = []
    #saltosDeRuta = 0
    #saltosTotales = 0
    lastMean = 0
    for element in sorted(tracedRoute, key=lambda obj: int(obj['hop_num'])):
        #saltosTotales += 1
        if element['ip_address'] is not None:
            deltaMean = element['rtt'] - lastMean
            lastMean = element['rtt']
            if deltaMean > 0 and not element['isIpPrivate']:
                x_saltos.append(element['hop_num'])
                rttEntreSalto.append(deltaMean)
                #saltosDeRuta += 1
    X = numpy.mean(rttEntreSalto)
    S = numpy.std(rttEntreSalto)
    zRTT = []
    for rtt in rttEntreSalto:
        numAux = (abs(rtt-X))/S
        zRTT.append(numAux)

    fig = plt.figure()
    fig.patch.set_facecolor('white')
    ax1 = fig.add_subplot(111)
    pylab.plot(x_saltos, rttEntreSalto, label= '')
    ax1.set_title("RTT por salto")
    ax1.set_xlabel('Salto')
    ax1.set_ylabel('RTT')
    plt.show()

    fig2 = plt.figure()
    fig2.patch.set_facecolor('white')
    ax2 = fig2.add_subplot(111)
    plt.bar(x_saltos, zRTT)
    ax2.axhline(tau, color="gray")
    ax2.set_title("RTT por Salto con el ZRTT")
    ax2.set_xlabel('Salto')
    ax2.set_ylabel('zRTT')
    plt.show()
    
def generateMap(tracedRoute):
    gmapsUrl = 'http://maps.google.com/maps/api/staticmap?size=1200x600&'
    allPaths = ''
    firstOne = True
    markers = set()

    for route in tracedRoute:
        if route['ip_address'] is not None:
            if route['isIpPrivate'] == False:
                marker = (route['country'], str(route['location'][0]), str(route['location'][1]))
                if marker not in markers:
                    if firstOne:
                        firstOne = False
                    else:
                        gmapsUrl += '&'
                        allPaths += '|'
                    gmapsUrl += 'markers=label:' + route['country'][:1] + '|' + str(route['location'][0]) + ',' + str(route['location'][1])
                    allPaths += str(route['location'][0]) + ',' + str(route['location'][1])
                    markers.add(marker)

    gmapsUrl += '&path=' + allPaths
    buffer = BytesIO(urllib.urlopen(gmapsUrl).read())
    image = Image.open(buffer)
    plt.imshow(image)
    plt.show()

def generateCimbalaMap(outliers):
    gmapsUrl = 'http://maps.google.com/maps/api/staticmap?size=1200x600&'
    allPaths = []
    firstOne = True
    markers = set()

    for route in outliers:
        if (route['srcIp'] is not None) and (route['dstIp'] is not None):
            if (route['srcIpIsPrivate'] == False) and (route['dstIpIsPrivate'] == False):
                #FUENTE:
                marker = (route['srcCountry'], str(route['srcLocation'][0]), str(route['srcLocation'][1]))
                
                if firstOne:
                    firstOne = False
                else:
                    gmapsUrl += '&'
                    #allPaths += '|'
                gmapsUrl += 'markers=label:' + route['srcCountry'][:1] + '|' + str(route['srcLocation'][0]) + ',' + str(route['srcLocation'][1])
                #allPaths += str(route['srcLocation'][0]) + ',' + str(route['srcLocation'][1])

                markers.add(marker)

                #DESTINO:
                marker = (route['dstCountry'], str(route['dstLocation'][0]), str(route['dstLocation'][1]))
                
                gmapsUrl += '&'
                #allPaths += '|'
                gmapsUrl += 'markers=label:' + route['dstCountry'][:1] + '|' + str(route['dstLocation'][0]) + ',' + str(route['dstLocation'][1])
                #allPaths += str(route['dstLocation'][0]) + ',' + str(route['dstLocation'][1])
                markers.add(marker)

                path = str(route['srcLocation'][0]) + ',' + str(route['srcLocation'][1]) + "|" + str(route['dstLocation'][0]) + ',' + str(route['dstLocation'][1])
                allPaths.append(path)

    for path in allPaths:
        gmapsUrl += '&path=' + path
    buffer = BytesIO(urllib.urlopen(gmapsUrl).read())
    image = Image.open(buffer)
    plt.imshow(image)
    plt.show()

# Argument parsing
def parseArguments():
    parser = argparse.ArgumentParser(description='Trace packages')
    parser.add_argument('host', help='a host to trace its route')
    parser.add_argument('-g', '--graph', const=True, default=False, nargs='?', help='generate graphics')
    parser.add_argument('-m', '--map', const=True, default=False, nargs='?', help='generate map')
    parser.add_argument('-j', '--json', const=True, default=False, nargs='?', help='print JSON and dump to file')
    return parser.parse_args()

# Here starts the main
args = parseArguments()
try:
   ipaddress.ip_address(args.host)
except:
    if args.host == 'AUSTRALIA':
        args.host = AUSTRALIA
    elif args.host == 'JAPAN':
        args.host = JAPAN
    elif args.host == 'INDIA':
        args.host = INDIA
    elif args.host == 'ICELAND':
        args.host = ICELAND

try:
    socket.gethostbyname(args.host)
except:
    print("Incorrect Host")
    exit()

trace(args.host, args.graph, args.map, args.json)