import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

arr = np.genfromtxt("resEj1-random.txt")
x = [row[4] for row in arr] #tiempo en MS
y = [row[2] for row in arr] #P


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

cota = '(x*100*1e5)'
grafCota = graph(cota, range(1,30))


promedio1NP = np.array(listaPromedio[0:99])
promedio2NP = np.array(listaPromedio[100:199])
promedio3NP = np.array(listaPromedio[200:299])
promedio4NP = np.array(listaPromedio[300:399])
promedio5NP = np.array(listaPromedio[400:499])
psNP = np.array(listaPares[0:99])

deAUno = range(1,30)

deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)

fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(psNP, promedio1NP,'r', label= '15x31')
pylab.plot(psNP, promedio2NP,'g', label= '49x10')
pylab.plot(psNP, promedio3NP,'b', label= '37x31')
pylab.plot(psNP, promedio4NP,'y', label= '33x46')
pylab.plot(psNP, promedio5NP,'black', label= '41x43')
pylab.plot(deAUno, grafCota,'bo', label= 'Cota de Complejidad')


ax1.set_title("Tiempo con tamaño de matriz random sobre cantidad de paredes destructibles")
ax1.set_xlabel('Cantidad de paredes Destructibles')
# ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
# ax1.set_yscale('linear')
# ax1.autoscale(enable=True, axis='both', tight=None)

leg = ax1.legend()

leg = plt.legend( loc = 'lower right')

plt.show()
