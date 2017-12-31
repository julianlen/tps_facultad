
# coding: utf-8

# # Instancias aleatorias y sus soluciones óptimas

# In[7]:



import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

plt.style.use('ggplot')


# ## Lectura de archivos

# In[8]:

namesHead = ['Config', 'Instancia', 'Corrida', 'Tiempo', 'Distancia', 'RCL']
ejemplo = pd.read_csv('ej4_exp1.csv', header = None, names = namesHead)


# ## Instancias vs distancia

# In[46]:

config1 = ejemplo[:9000]
config2 = ejemplo[9001:18000]
config3 = ejemplo[18001:27000]
config4 = ejemplo[27001:36000]

config1 = config1.groupby('Corrida').mean()
#config1 = config1.groupby('RCL')
config2 = config2.groupby('Corrida').mean()
#config2 = config2.groupby('RCL')
config3 = config3.groupby('Corrida').mean()
#config3 = config3.groupby('RCL')
config4 = config4.groupby('Corrida').mean()
#config4 = config4.groupby('RCL')

config1['Nombre'] = "Config1"
config2['Nombre'] = "Config2"
config3['Nombre'] = "Config3"
config4['Nombre'] = "Config4"

result = pd.concat([config1,config2,config3,config4]).reset_index()

#print(result)

sns.barplot(x = 'RCL', y = 'Tiempo', hue = "Nombre", ci = 0.68, data = result)
plt.show()

sns.barplot(x = 'RCL', y = 'Distancia', hue = "Nombre", ci = 0.68, data = result)
plt.show()


# print(config2)
# print(config3)
# print(config4)
#paraGraficar = pd.concat([paraGraficarSG['distancia'], paraGraficarPC['distanciaNueva'], paraGraficarPYRP['distanciaNueva'], paraGraficarGRASP['distancia'], paraGraficarOp['distancia']], axis=1, keys=['Solución golosa', 'Permuta el camino', 'Permuta y reemplaza pokeparadas', 'GRASP', 'Solución óptima'])

# fig, ax = plt.subplots()

# paraGraficar.plot.bar(ax=ax)

# plt.xlabel('Instancia')
# plt.ylabel('Distancia')
# ax.set_xlim([0.5, 16.5])
# plt.rcParams.update({'font.size': 8})

# legend = ax.legend([u'Solución golosa', 'Permuta el camino', 'Permuta y reemplaza pokeparadas', 'GRASP', u'Solución óptima'], loc = 'upper center', bbox_to_anchor = (0.5, -0.1), fancybox = True, shadow = True, ncol = 2)
# frame = legend.get_frame()
# frame.set_facecolor('white')
# frame.set_linewidth(0)

# #plt.show()
# plt.gcf().set_size_inches(7, 5)
# plt.savefig('expAleatOp_instancia_distancia.pdf', format='pdf', bbox_inches = 'tight', dpi = 100)


# ## Tiempo vs cantidad de nodos

# In[ ]:

solGolosa['cantNodos'] = solGolosa['cantGimnasios'] + solGolosa['cantPokeparadas']
permutaCamino['cantNodos'] = permutaCamino['cantGimnasios'] + permutaCamino['cantPokeparadas']
permutaYReemplazaPokeparadas['cantNodos'] = permutaYReemplazaPokeparadas['cantGimnasios'] + permutaYReemplazaPokeparadas['cantPokeparadas']
GRASP['cantNodos'] = GRASP['cantGimnasios'] + GRASP['cantPokeparadas']
op['cantNodos'] = op['cantGimnasios'] + op['cantPokeparadas']

#permutaCamino['tiempo'] = permutaCamino['tiempo'] + solGolosa['tiempo']
#permutaYReemplazaPokeparadas['tiempo'] = permutaYReemplazaPokeparadas['tiempo'] + solGolosa['tiempo']

fig, ax = plt.subplots()

ax = solGolosa.groupby('cantNodos').mean()['tiempo'].plot(color='forestgreen', linewidth = 1)
permutaCamino.groupby('cantNodos').mean()['tiempo'].plot(color='purple', linewidth = 1, ax=ax)
permutaYReemplazaPokeparadas.groupby('cantNodos').mean()['tiempo'].plot(color='indianred', linewidth = 1, ax=ax)
GRASP.groupby('cantNodos').mean()['tiempo'].plot(color='m', linewidth = 1, ax=ax)
op.groupby('cantNodos').mean()['tiempo'].plot(color='royalblue', linewidth = 1, ax=ax)

plt.xlabel('n + m')
plt.ylabel('Tiempo (ciclos)')
#ax.set_ylim([-100000000, 1500000000])
plt.rcParams.update({'font.size': 8})

ax.set_yscale('log')


legend = ax.legend([u'Solución golosa', 'Permuta el camino', 'Permuta y reemplaza pokeparadas', 'GRASP', u'Solución óptima'], loc = 'upper center', bbox_to_anchor = (0.5, -0.1), fancybox = True, shadow = True, ncol = 2)
frame = legend.get_frame()
frame.set_facecolor('white')
frame.set_linewidth(0)

#plt.show()
plt.gcf().set_size_inches(6, 4)
plt.savefig('expAleatOp_cantNodos_tiempo.pdf', format='pdf', bbox_inches = 'tight', dpi = 100)

