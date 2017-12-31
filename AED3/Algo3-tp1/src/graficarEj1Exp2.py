import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

arr = np.genfromtxt("ej1Exp2Nuevo.txt")
x = [row[0] for row in arr] #tiempo en MS
# y = [row[1] for row in arr] #arq (arq,cani)
y = [row[1] for row in arr] #cani (arq,cani)
# total = [row[2] for row in arr] #total (arq,cani)


def promedio(list):
   return sum(list)/len(list)

def graph(formula, x_range):
    x = np.array(x_range)
    y = eval(formula)
    return y

k = 0
listaPromedio = []
listaPares = []
listaPers = []
# print(len(x))
while k < len(x):
  subList = x[k:k+30]
  listaPromedio.append(promedio(subList))
  listaPares.append(y[k])
  # promedios = ([np.average(subList), y[k], z[k], total[k]])
  # listaPromedio.append(promedios)
  k += 30
# print(listaPares)
# np.savetxt("mydata.csv", listaPromedio, fmt='%1u' )

cota = '((x**6))*(5**(x**2))'
grafCota = graph(cota, range(1,6))

promedio1NP = np.array(listaPromedio) # 1arq
arqs1NP = np.array(listaPares)

# PersNP = np.array(listaPers)

deAUno = range(1,6)

deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)

fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(arqs1NP, promedio1NP, color='red', marker='o', label= '0 Arqueologos')
pylab.plot(deAUno, grafCota,'black', label= 'Cota de Complejidad')


ax1.set_title("Tiempo sobre cantidad de canibales")
ax1.set_xlabel('Cantidad de canibales')
ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
ax1.set_yscale('log', basey=2)

leg = ax1.legend()

leg = plt.legend( loc = 'upper left')

plt.show()
