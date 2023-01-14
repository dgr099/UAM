from Plantillas.Clasificador import ClasificadorGenetico
from Plantillas import Datos
dataPath = './ConjuntoDatos/'
from Plantillas import Datos, EstrategiaParticionado, Roc
from Plantillas.Clasificador import ClasificadorGenetico

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt



"""
estrategiaVS = EstrategiaParticionado.ValidacionSimple(1, 0.3)

print("Xor: ")
xor = Datos.Datos(dataPath + 'xor.csv')
print(xor.diccionarios)
partition = estrategiaVS.creaParticiones(xor.datos)
d_train = xor.extraeDatos(partition.indicesTrain)
d_test = xor.extraeDatos(partition.indicesTest)
clasificador = ClasificadorGenetico(populationSize=40, numGenerations=100, maxRules=10, mutProb=0.1)
clasificador.entrenamiento(d_train, nominalAtributos=xor.nominalAtributos, diccionario=xor.diccionarios)
print("Individuo: ", clasificador.individuo)
errors = 0
#imprime 5 para ver
for i in range(len(d_test)):
    #print("Caso de prueba: ", d_test[i])
    pred = clasificador.clasifica([d_test[i][:-1]], nominalAtributos=xor.nominalAtributos, diccionario=xor.diccionarios)[0]
    #print("Clase: ", d_test[i][-1], " Clase predecida ", pred)
    if(pred!=d_test[i][-1]):
        errors+=1
print("Numero de errores: " + str(errors) + "/" + str(len(d_test)))
"""

"""
print("titanic: ")
titanic = Datos.Datos(dataPath + 'titanic.csv')
print(titanic.diccionarios)
partition = estrategiaVS.creaParticiones(titanic.datos)
d_train = titanic.extraeDatos(partition.indicesTrain)
d_test = titanic.extraeDatos(partition.indicesTest)
clasificador = ClasificadorGenetico(populationSize=100, numGenerations=300, maxRules=50, mutProb=0.1)
clasificador.entrenamiento(d_train, nominalAtributos=titanic.nominalAtributos, diccionario=titanic.diccionarios)
print("Individuo: ", clasificador.individuo)
errors = 0
for i in range(len(d_test)):
    #print("Caso de prueba: ", d_test[i])
    pred = clasificador.clasifica([d_test[i]], nominalAtributos=titanic.nominalAtributos, diccionario=titanic.diccionarios)[0]
    #print("Clase: ", d_test[i][-1], " Clase predecida ", pred)
    if(pred!=d_test[i][-1]):
        errors+=1
print("Numero de errores: " + str(errors) + "/" + str(len(d_test)))
"""

estrategiaVS = EstrategiaParticionado.ValidacionSimple(1, 0.3)
xor = Datos.Datos(dataPath + 'xor.csv')
titanic = Datos.Datos(dataPath + 'titanic.csv')
clasificador = ClasificadorGenetico(populationSize=20, numGenerations=25, maxRules=10, mutProb=0.05, elitismo=0.1, parents=0.5)
print(clasificador.validacion(estrategiaVS, xor, clasificador))
print(clasificador.validacion(estrategiaVS, titanic, clasificador))