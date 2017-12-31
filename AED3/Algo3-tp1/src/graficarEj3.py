import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 2 -exp > resEj2.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

arr = np.genfromtxt("ej3Exp3.txt")
x = [row[0] for row in arr]
y = [row[1] for row in arr]
nroMochilas = [row[3] for row in arr]


def graph(formula, x_range):
    x = np.array(x_range)
    y = eval(formula)
    return y

def promedio(list):
   return sum(list)/len(list)

k = 0
listaPromedio = []
listaProducTamMochilas = []
listaMochilas = []
while k < len(x):
  subList = x[k:k+50]
  listaPromedio.append(promedio(subList))
  listaProducTamMochilas.append(y[k])
  listaMochilas.append(nroMochilas[k])
  k += 50

k=0
pares=[]
while k < len(listaProducTamMochilas):
  pares.append( [ listaPromedio[k], listaProducTamMochilas[k], listaMochilas[k] ] )
  k += 1

sorted(pares, key=lambda x: x[2])

unaMochila = []
dosMochila = []
tresMochila = []
tiemposUno = []
tiemposDos = []
tiemposTres = []

k=0
while k < len(pares):
  if pares[k][2] == 1:
    unaMochila.append(pares[k][1])
    tiemposUno.append(pares[k][0])
  elif pares[k][2] == 2:
    dosMochila.append(pares[k][1])
    tiemposDos.append(pares[k][0])
  else:
    tresMochila.append(pares[k][1])
    tiemposTres.append(pares[k][0])
  k += 1



promedioUnoNP = np.array(tiemposUno)
promedioDosNP = np.array(tiemposDos)
promedioTresNP = np.array(tiemposTres)
unasMochilasNP = np.array(unaMochila)
dosMochilasNP = np.array(dosMochila)
tresMochilasNP = np.array(tresMochila)

cota = 'x*x*x*x'
grafCota = graph(cota, range(1,30))
deAUno = range(1,30)
deAUno = np.array(deAUno)



fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(unasMochilasNP, promedioUnoNP, color='red', marker='o', label= 'una mochila')
pylab.plot(dosMochilasNP, promedioDosNP, color='blue', marker='o', label= 'dos mochilas')
pylab.plot(tresMochilasNP, promedioTresNP, color='green', marker='o', label= 'tres mochilas')
pylab.plot(deAUno, grafCota,'black', label= 'Cota de Complejidad')


ax1.set_title("Mochilas de distintos tamaños")
ax1.set_xlabel('capacidad de las mochilas y cantidad de tesoros totales')
ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en microsegundos')
ax1.set_yscale('linear')

leg = ax1.legend()

leg = plt.legend( loc = 'upper left')

plt.show()
