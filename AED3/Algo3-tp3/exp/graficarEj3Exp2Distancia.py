import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("rsalida.txt", delimiter=',')
#arr = np.loadtxt("experimentoLoco3.data", delimiter=',')
arr = np.loadtxt("Salidas/ej3_salida2_exp3.txt", delimiter=',')
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
while k < len(dist):
  subList = dist[k:k+30]
  promedioTiempo.append(promedio(subList))
  nMasm.append(m[k] + n[k])
  k += 30

promedio1NP = np.array(promedioTiempo[0:49]) #vecindario A
promedio2NP = np.array(promedioTiempo[50:99]) #vecindario B
promedio3NP = np.array(promedioTiempo[100:149]) # Greedy
nm = np.array(nMasm[0:49])





# cota = 'factorial(x)*x*x*x'
# grafCota = graph(cota, range(1,30))
# deAUno = range(1,30)
# deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)


fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(nm, promedio1NP,'gD', label= 'vecindario a')
#pylab.plot(nm, promedio2NP,'bo', label= 'vecindario b')
pylab.plot(nm, promedio3NP,'r^', label= 'greedy')
# pylab.plot(deAUno, grafCota,color='black', marker='s', label= 'Cota de Complejidad')
# fig2 = plt.figure()
# fig2.patch.set_facecolor('white')
# ax2 = fig2.add_subplot(111)
# pylab.plot(nm, promedio1NP,'r^', label= 'backtracking')
# pylab.plot(nm, promedio2NP,'g*', label= 'vecindario a')
# pylab.plot(nm, promedio3NP,'bo', label= 'vecindario b')





ax1.set_title("Distancia segun Estaciones")
ax1.set_xlabel('Cantidad de gimnasios + pokeparadas')
ax1.set_ylabel('Distancias')

# ax2.set_title("Distancia segun Estaciones para vecindario B")
# ax2.set_xlabel('Cantidad de gimnasios + pokeparadas')
# ax2.set_ylabel('Distancias')

leg = ax1.legend()
#leg = ax2.legend()
leg = plt.legend( loc = 'upper left')

plt.show()
