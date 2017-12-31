import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys
import plotly.plotly as py
import plotly.graph_objs as go


# Antes de usar esto, tirar en consola "./tp1 1 -exp > resEj1.txt". CUIDADO CON PISAR EL ARCHIVO ANTERIOR

# arr = np.genfromtxt("rsalida.txt", delimiter=',')
arr = np.loadtxt("salida_random_ej2.data", delimiter=',')
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
nMasm = [2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
estaciones2 = []
estaciones3 = []
estaciones4 = []
estaciones5 = []
estaciones6 = []
estaciones7 = []
estaciones8 = []
estaciones9 = []
estaciones10 = []
estaciones11 = []
estaciones12 = []
estaciones13 = []
estaciones14 = []
estaciones15 = []
estaciones16 = []
while k < len(tiempo):
  estaciones = m[k] + n[k]
  if estaciones == 2:
    subList = tiempo[k:k+150]
    estaciones2.append(promedio(subList))
    k += 150
  elif estaciones == 3:
    subList = tiempo[k:k+150]
    estaciones3.append(promedio(subList))
    k += 150
  elif estaciones == 4:
    subList = tiempo[k:k+150]
    estaciones4.append(promedio(subList))
    k += 150
  elif estaciones == 5:
    subList = tiempo[k:k+150]
    estaciones5.append(promedio(subList))
    k += 150
  elif estaciones == 6:
    subList = tiempo[k:k+150]
    estaciones6.append(promedio(subList))
    k += 150
  elif estaciones == 7:
    subList = tiempo[k:k+150]
    estaciones7.append(promedio(subList))
    k += 150
  elif estaciones == 8:
    subList = tiempo[k:k+150]
    estaciones8.append(promedio(subList))
    k += 150
  elif estaciones == 9:
    subList = tiempo[k:k+150]
    estaciones9.append(promedio(subList))
    k += 150
  elif estaciones == 10:
    subList = tiempo[k:k+150]
    estaciones10.append(promedio(subList))
    k += 150
  elif estaciones == 11:
    subList = tiempo[k:k+150]
    estaciones11.append(promedio(subList))
    k += 150
  elif estaciones == 12:
    subList = tiempo[k:k+150]
    estaciones12.append(promedio(subList))
    k += 150
  elif estaciones == 13:
    subList = tiempo[k:k+150]
    estaciones13.append(promedio(subList))
    k += 150
  elif estaciones == 14:
    subList = tiempo[k:k+150]
    estaciones14.append(promedio(subList))
    k += 150
  elif estaciones == 15:
    subList = tiempo[k:k+150]
    estaciones15.append(promedio(subList))
    k += 150
  elif estaciones == 16:
    subList = tiempo[k:k+150]
    estaciones16.append(promedio(subList))
    k += 150


promedio1NP = np.array(promedioTiempo)
nm = np.array(nMasm)

t2 = go.Box(
    y=estaciones2,
    name = '2 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t3 = go.Box(
    y=estaciones3,
    name = '3 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t4 = go.Box(
    y=estaciones4,
    name = '4 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t5 = go.Box(
    y=estaciones5,
    name = '5 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t6 = go.Box(
    y=estaciones6,
    name = '6 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t7 = go.Box(
    y=estaciones7,
    name = '7 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t8 = go.Box(
    y=estaciones8,
    name = '8 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t9 = go.Box(
    y=estaciones9,
    name = '9 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t10 = go.Box(
    y=estaciones10,
    name = '10 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t11 = go.Box(
    y=estaciones11,
    name = '11 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t12 = go.Box(
    y=estaciones12,
    name = '12 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t13 = go.Box(
    y=estaciones13,
    name = '13 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t14 = go.Box(
    y=estaciones14,
    name = '14 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t15 = go.Box(
    y=estaciones15,
    name = '15 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
t16 = go.Box(
    y=estaciones16,
    name = '16 estaciones',
    marker = dict(
        color = 'rgb(0, 128, 128)',
    )
)
dataHelper = [t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16]

py.offline.plot(dataHelper)


cota = 'x*x*x*x*x'
grafCota = graph(cota, range(1,15))
deAUno = range(1,15)
deAUno = np.array(deAUno)

# medianaX  = mediana(x)
# modaX     = moda(x)


# fig = plt.figure()
# fig.patch.set_facecolor('white')
# ax1 = fig.add_subplot(111)
# pylab.plot(nm, promedio1NP,'ro', label= 'random')
# pylab.plot(deAUno, grafCota,color='black', marker='s', label= 'Cota de Complejidad')


# ax1.set_title("Tiempo segun tamaño de la mochila")
# ax1.set_xlabel('Cantidad de gimnasios + pokeparadas')
# ax1.set_ylabel('Tiempo de procesamiento en ns')

# leg = ax1.legend()

# leg = plt.legend( loc = 'upper left')

# plt.show()
