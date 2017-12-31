import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("ej1Res.txt")
arr = np.genfromtxt("ej1Exp1Nuevo.txt")
x = [row[0] for row in arr] #tiempo en MS
# y = [row[1] for row in arr] #arq (arq,cani)
y = [row[2] for row in arr] #cani (arq,cani)
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
grafCota = graph(cota, range(1,5))

promedio1NP = np.array(listaPromedio[0:1]) # 1arq
promedio2NP = np.array(listaPromedio[1:3]) # 2arq
promedio3NP = np.array(listaPromedio[3:6]) # 3arq
promedio4NP = np.array(listaPromedio[6:9]) # 4arq
# promedio5NP = np.array(listaPromedio[10:15]) # 5arq
# promedio6NP = np.array(listaPromedio[15:21]) # 6arq
# promedio7NP = np.array(listaPromedio[21:28]) # 7arq
arqs1NP = np.array(listaPares[0:1])
arqs2NP = np.array(listaPares[1:3])
arqs3NP = np.array(listaPares[3:6])
arqs4NP = np.array(listaPares[6:9])
# arqs5NP = np.array(listaPares[10:15])
# arqs6NP = np.array(listaPares[15:21])
# arqs7NP = np.array(listaPares[21:28])
# PersNP = np.array(listaPers)
print(listaPromedio[2])

deAUno = range(1,5)

deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)

fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(arqs1NP, promedio1NP, color='red', marker='o', label= '1 Arqueologo')
pylab.plot(arqs2NP, promedio2NP, color='blue', marker='o', label= '2 Arqueologos')
pylab.plot(arqs3NP, promedio3NP, color='green', marker='o', label= '3 Arqueologos')
pylab.plot(arqs4NP, promedio4NP, color='orange', marker='o', label= '4 Arqueologos')
# pylab.plot(arqs5NP, promedio5NP, color='purple', marker='o', label= '5 Arqueologos')
# pylab.plot(arqs6NP, promedio6NP, color='orange', marker='o', label= '6 Arqueologos')
# pylab.plot(arqs7NP, promedio7NP, color='brown', marker='o', label= '7 Arqueologos')
pylab.plot(deAUno, grafCota,'black', label= 'Cota de Complejidad')


ax1.set_title("Tiempo sobre cantidad de canibales (y arqueologos)")
ax1.set_xlabel('Cantidad de canibales')
ax1.set_xscale('linear')
ax1.set_ylabel('Tiempo de procesamiento en ns')
ax1.set_yscale('log', basey=2)

leg = ax1.legend()

leg = plt.legend( loc = 'lower right')

plt.show()
