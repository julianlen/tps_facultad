import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("rsalida.txt", delimiter=',')
arr = np.loadtxt("salida_exp3_ej1.data", delimiter=',')
tiempo    = [row[0] for row in arr] #tiempo en MS
n         = [row[1] for row in arr] #P
m         = [row[2] for row in arr] #P
mochila   = [row[3] for row in arr] #P
dist      = [row[4] for row in arr] #P
visitados = [row[5] for row in arr] #P


def promedio(list):
   return sum(list)/len(list)

def graph(formula, x_range):
    x = np.array(x_range)
    y = eval(formula)
    return y

def factorial(list):
    res = []
    for number in list:
      res.append(math.factorial(number))
    return res

k = 0
promedioTiempo = []
nMasm = []
while k < len(tiempo):
  subList = tiempo[k:k+30]
  promedioTiempo.append(promedio(subList))
  nMasm.append(m[k] + n[k])
  k += 30


promedio1NP = np.array(promedioTiempo)
nm = np.array(nMasm)


cota = 'factorial(x)*x'
grafCota = graph(cota, range(1,15))
deAUno = range(1,15)
deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)


fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(nm, promedio1NP,'ro', label= 'random')
# pylab.plot(deAUno, grafCota,color='black', marker='s', label= 'Cota de Complejidad')


ax1.set_title("Tiempo segun tamaño de la mochila")
ax1.set_xlabel('Cantidad de gimnasios + pokeparadas')
# ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
# ax1.set_yscale('linear')
# ax1.autoscale(enable=True, axis='both', tight=None)

leg = ax1.legend()

leg = plt.legend( loc = 'upper left')

plt.show()
