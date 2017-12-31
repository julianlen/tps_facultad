import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("rsalida.txt", delimiter=',')
arr = np.loadtxt("Salidas/salida_exp1_ej3a.data", delimiter=',')
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
  subList = tiempo[k:k+1000]
  promedioTiempo.append(promedio(subList))
  nMasm.append(m[k] + n[k])
  k += 1000


promedio1NP = np.array(promedioTiempo[0:14])
promedio2NP = np.array(promedioTiempo[15:29])
promedio3NP = np.array(promedioTiempo[30:44])
nm = np.array(nMasm[0:14])


cota = 'factorial(x)*x*x*x'
deAUno = range(1,8)
grafCota = graph(cota, deAUno)
deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)


fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(nm, promedio1NP,'red', marker='o', label= '4 Gimnasios')
pylab.plot(nm, promedio2NP,'blue', marker='*', label= '5 Gimnasios')
pylab.plot(nm, promedio3NP,'green', marker='^', label= '6 Gimnasios')
#pylab.plot(deAUno, grafCota,color='black', marker='s', label= 'Cota de Complejidad')


ax1.set_title("Tiempo segun cantidad de gimnasios vecindad A")
ax1.set_xlabel('Cantidad de gimnasios + pokeparadas')
# ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
# ax1.set_yscale('linear')
# ax1.autoscale(enable=True, axis='both', tight=None)

leg = ax1.legend()

leg = plt.legend( loc = 'upper right')

plt.show()
