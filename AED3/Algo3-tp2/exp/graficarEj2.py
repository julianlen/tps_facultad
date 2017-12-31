import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("resEj2-random.txt")
arr = np.genfromtxt("resEj2-fijo.txt")
x = [row[3] for row in arr] #tiempo en MS
y = [row[0] for row in arr] #tamMatriz


def promedio(list):
   return sum(list)/len(list)

def graph(formula, x_range):
    x = np.array(x_range)
    y = eval(formula)
    return y

k = 0
listaPromedio = []
listaPares = []
# print(len(x))
while k < len(x):
  subList = x[k:k+50]
  listaPromedio.append(promedio(subList))
  listaPares.append(y[k])
  # promedios = ([np.average(subList), y[k], z[k], total[k]])
  # listaPromedio.append(promedios)
  k += 50
# print(listaPares)
# np.savetxt("mydata.csv", listaPromedio, fmt='%1u' )

cota = '((x*x)*(np.log10(x*x))*1e3)'
grafCota = graph(cota, range(1,200))


promedio1NP = np.array(listaPromedio[0:499])
promedio2NP = np.array(listaPromedio[500:999])
promedio3NP = np.array(listaPromedio[1000:1499])
tamanosMatricesNP = np.array(listaPares[0:499])

deAUno = range(1,200)

deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)

fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(tamanosMatricesNP, promedio1NP,'r', label= 'Muchas paredes destructibles')
pylab.plot(tamanosMatricesNP, promedio2NP,'g', label= 'Sin Paredes')
pylab.plot(tamanosMatricesNP, promedio3NP,'black', label= 'Solo paredes indestructibles')
pylab.plot(deAUno, grafCota,'bo', label= 'Cota de Complejidad')


ax1.set_title("Tiempo con sobre matrices cuadradas de tamaño linealmente creciente")
ax1.set_xlabel('Tamaño de (uno de los lados de) la matriz')
# ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
# ax1.set_yscale('linear')
# ax1.autoscale(enable=True, axis='both', tight=None)

leg = ax1.legend()

leg = plt.legend( loc = 'upper left')

plt.show()
