from abc import ABCMeta, abstractmethod
from collections import Counter
import copy
import random
import numpy as np
import pandas as pd
import math
import sys

from sklearn.model_selection import train_test_split, cross_val_score

from Plantillas.EstrategiaParticionado import ValidacionCruzada

def calcularMediasDesv(datos, nominalAtributos=None):
    num_atributes = datos.shape[1]
    means_and_desvs = [] # Array con tuplas (mean, desv)
    for atrib_index in range(num_atributes):
        if nominalAtributos is None or nominalAtributos[atrib_index] == False:
            atrib_col = pd.to_numeric(datos[:,atrib_index])
            mean, desv = atrib_col.mean(), atrib_col.std()
            means_and_desvs.append((mean, desv))
        else:
            means_and_desvs.append((None, None))
    return means_and_desvs

def normalizarDatos(datos, means_and_desvs, nominalAtributos=None):
    for i in range(datos.shape[0]):
        for j in range(datos.shape[1]):
            if nominalAtributos is None or nominalAtributos[j] == False:
                mean, desv = means_and_desvs[j]
                datos[i][j] = (datos[i][j] - mean) / desv

class Clasificador:
  
  # Clase abstracta
  __metaclass__ = ABCMeta
  
  # Metodos abstractos que se implementan en casa clasificador concreto
  @abstractmethod
  # TODO: esta funcion debe ser implementada en cada clasificador concreto. Crea el modelo a partir de los datos de entrenamiento
  # datosTrain: matriz numpy con los datos de entrenamiento
  # nominalAtributos: array bool con la indicatriz de los atributos nominales
  # diccionario: array de diccionarios de la estructura Datos utilizados para la codificacion de variables discretas
  def entrenamiento(self,datosTrain,nominalAtributos,diccionario):
    pass
  
  
  @abstractmethod
  # TODO: esta funcion debe ser implementada en cada clasificador concreto. Devuelve un numpy array con las predicciones
  # datosTest: matriz numpy con los datos de validaci�n
  # nominalAtributos: array bool con la indicatriz de los atributos nominales
  # diccionario: array de diccionarios de la estructura Datos utilizados para la codificacion de variables discretas
  def clasifica(self,datosTest,nominalAtributos,diccionario,getProbabilities=False):
    pass
  
  # Obtiene el numero de aciertos y errores para calcular la tasa de fallo
  def error(self,datos,pred):
    # Aqui se compara la prediccion (pred) con las clases reales y se calcula el error   
    return (datos.shape[0] - [pred[i] - pd.to_numeric(datos[i]) for i in range(datos.shape[0])].count(0)) / datos.shape[0]
  
  # Realiza una clasificacion utilizando una estrategia de particionado determinada
  def validacion(self,particionado,dataset,clasificador,seed=None):
    # Creamos las particiones siguiendo la estrategia llamando a particionado.creaParticiones
    # - Para validacion cruzada: en el bucle hasta nv entrenamos el clasificador con la particion de train i
    # y obtenemos el error en la particion de test i
    # - Para validacion simple (hold-out): entrenamos el clasificador con la particion de train
    # y obtenemos el error en la particion test. Otra opci�n es repetir la validaci�n simple un n�mero especificado de veces, obteniendo en cada una un error. Finalmente se calcular�a la media.
    partitions = []
    if isinstance(particionado, ValidacionCruzada):
        partitions = particionado.creaParticiones(dataset.datos)
    else:
        for _ in range(particionado.repetitions):
            partitions.append(particionado.creaParticiones(dataset.datos))

    errors = []
    for partition in partitions:
      d_train = dataset.extraeDatos(partition.indicesTrain)
      d_test = dataset.extraeDatos(partition.indicesTest)
      clasificador.entrenamiento(d_train, dataset.nominalAtributos, dataset.diccionarios)
      predictions = clasificador.clasifica(d_test[:, :-1], dataset.nominalAtributos, dataset.diccionarios)
      #print(predictions)
      errors.append(clasificador.error(d_test[:,-1], predictions))
    return errors



class ClasificadorNaiveBayes(Clasificador):

  def __init__(self, laplace=True):
    self.laplace = laplace

  def entrenamiento(self, datosTrain, nominalAtributos, diccionario=None):
      num_atributes = datosTrain.shape[1] - 1
      class_column = datosTrain[:,-1]
      values_set_h = sorted(set(class_column)) # Posibles valores de la hipotesis ordenados

      self.prioris = {}
      self.verosimilitudes = []

      # Calculamos las probabilidades a priori de cada valor de clase P(c)
      for value in values_set_h:
        self.prioris[value] = sum(class_column == value) / len(class_column)

      # Una vez tenemos los prioris, guardamos las verosimilitudes necesarias para clasificar      
      for atrib_index in range(num_atributes):
        atrib_col = datosTrain[:,atrib_index]
        values_set_a = sorted(set(atrib_col)) # Posibles valores del atributo ordenados

        dicc = {}
        if(nominalAtributos[atrib_index] == True): # En caso de atributos nominales, se calculan las condiciondas
          # Inicializamos los diccionarios a cero
          for value_a in values_set_a:
            dicc_2 = {}
            for value_h in values_set_h:
              dicc_2[value_h] = 0
            dicc[value_a] = dicc_2

          # Realizamos conteo de cada hipotesis por cada atributo
          for value_a, value_h in zip(atrib_col, class_column):
            dicc[value_a][value_h] += 1

          # Comprobamos si hay algun cero en alguna posicion para aplicar Laplace
          zero_flag = 0
          for value_a, value_h in zip(values_set_a, values_set_h):
            if dicc[value_a][value_h] == 0: 
              zero_flag = 1
              break

          # En caso de que haya algun cero, usamos la correccion de Laplace
          if zero_flag == 1 and self.laplace:
            for value_a in values_set_a:
              for value_h in values_set_h:
                dicc[value_a][value_h] += 1

          # Obtenemos las verosimilitudes
          for value_a in dicc.keys():
            for value_h in dicc[value_a].keys():
              dicc[value_a][value_h] /= (sum(class_column == value_h) + len(values_set_a) * zero_flag)

        else: # En caso de atributos continuos NB supone que sigue una distribución normal
          atrib_col = pd.to_numeric(atrib_col)
          dicc["media"], dicc["desv"] = atrib_col.mean(), atrib_col.std()

        # Tanto si es nominal como continuo, se genera un diccionario, aunque con formas diferentes
        self.verosimilitudes.append(dicc)

    
  def clasifica(self,datosTest,nominalAtributos,diccionario=None,getProbabilities=False):
    predicciones=[]
    for test_case in datosTest:

      max_prob = -1     # Para obligar a que entre en el if
      for h in self.prioris: #compruebo para todas las hipotesis cual tiene mayor posteriori      
        posteriori = self.prioris[h] #num de numerador que siempre termina multiplicando por la hipótesis
        for atrib, value in enumerate(test_case): #recorro todos los valores del dataset para appendear las predicciones
          if nominalAtributos[atrib] == True:
            posteriori *= self.verosimilitudes[atrib][value][h] #cojo la verosimilitud de ese atributo para el valor y la hipótesis
          else:
            mean = self.verosimilitudes[atrib]["media"]
            desv = self.verosimilitudes[atrib]["desv"]
            x = pd.to_numeric(test_case[atrib])
            posteriori *= math.exp(-(x-mean)**2 / (2 * desv**2)) / (desv * (2 * math.pi)**(0.5))

        if(posteriori > max_prob): #si la prob es mayor que la mayor anterior
          max_prob = posteriori #cambiamos la mejor probabilidad
          MAP = h #y cambiamos la hipótesis de MAP

      predicciones.append(MAP) #appendeamos la predicción
    
    return predicciones #retornamos las predicciones


class ClasificadorNaiveBayesSk(Clasificador):

  def __init__(self, metodoNB):
      self.metodoNB = metodoNB
      
  def entrenamiento(self, datosTrain, nominalAtributos=None, diccionario=None, ):
    x_train = datosTrain[:,:-1]
    y_train = datosTrain[:,-1]
    self.metodoNB.fit(x_train, y_train)
    
  def clasifica(self, datosTest, nominalAtributos=None, diccionario=None,getProbabilities=False):
    return self.metodoNB.predict(datosTest)
  
  def validacion(self, particionado, dataset, clasificador, seed=None, ):
    x = dataset.datos[:,:-1]
    y = dataset.datos[:,-1]
    if isinstance(particionado, ValidacionCruzada):
        errors = [1 - score for score in cross_val_score(clasificador.metodoNB, x, y, cv=particionado.repetitions)]
    else:
        errors = []
        for _ in range(particionado.repetitions):
          x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=particionado.test_size)
          self.entrenamiento(np.concatenate((x_train, np.transpose([y_train])), axis=1))
          predictions = self.clasifica(x_test)
          errors.append(super().error(y_test, predictions))
        
    return errors

  
class ClasificadorKNN(Clasificador):
  
  def __init__(self, k, normalize=True):
    self.k = k
    self.normalize = normalize

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,):
    self.means_and_desvs = calcularMediasDesv(datosTrain[:,:-1], nominalAtributos)
    self.datosTrain = np.array(datosTrain)
    if self.normalize == True:
      normalizarDatos(self.datosTrain[:,:-1], self.means_and_desvs, nominalAtributos)
    
  def clasifica(self,datosTest,nominalAtributos=None,diccionario=None,getProbabilities=False):
    predicciones = []
    num_atributes = datosTest.shape[1] - 1
    
    if self.normalize == True:
      normalizarDatos(datosTest, self.means_and_desvs, nominalAtributos)
    
    # Para cada caso, comprobamos las distancias a todos los casos de train
    for test_case in datosTest:
      
      k_neighbors = np.empty((0,2))
      furthest_neighbor = -1 # Contendra el indice dentro de k_neighbors
      for train in self.datosTrain:

        euclidean_distance = 0
        for i in range(num_atributes):
          euclidean_distance += (test_case[i] - train[i])**2
        
        if len(k_neighbors) < self.k: # Inicializamos con los primeros 'k' casos de train
          k_neighbors = np.append(k_neighbors, [[euclidean_distance, train[-1]]], axis=0)
          if euclidean_distance > furthest_neighbor: # Vamos actualizando el mas lejano para ganar tiempo
            furthest_neighbor = len(k_neighbors) - 1
          
        # Para el resto de casos, vamos comprobando si es mas cercano que el mayor de los vecinos actuales
        elif euclidean_distance < k_neighbors[furthest_neighbor][0]:
          k_neighbors[furthest_neighbor] = [euclidean_distance, train[-1]]
          furthest_neighbor = np.argmax(k_neighbors[:,0])
        
      # most_common(1) devuelve el primer elemento mas comun (si fuese 2, devolveria los dos primeros)
      predicciones.append(Counter(k_neighbors[:,1]).most_common(1)[0][0]) # Guardamos la hipotesis mas comun
    
    return predicciones


class ClasificadorKNN_SK(Clasificador):
  def __init__(self, knn_sk, normalize=True):
    self.normalize = normalize
    self.clasificadorKNN = knn_sk

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,):
    self.datosTrain = np.array(datosTrain)
    self.means_and_desvs = calcularMediasDesv(self.datosTrain[:,:-1], nominalAtributos)
    if self.normalize == True:
      normalizarDatos(self.datosTrain[:,:-1], self.means_and_desvs, nominalAtributos)
    x_train = self.datosTrain[:,:-1]
    y_train = self.datosTrain[:,-1]
    self.clasificadorKNN.fit(x_train, y_train)
    
  def clasifica(self,datosTest,nominalAtributos=None,diccionario=None,getProbabilities=False):
    if self.normalize == True:
      normalizarDatos(datosTest, self.means_and_desvs, nominalAtributos)
    return self.clasificadorKNN.predict(datosTest)

  def validacion(self, particionado, dataset, clasificador, seed=None, ):
    x = dataset.datos[:,:-1]
    y = dataset.datos[:,-1]
    if isinstance(particionado, ValidacionCruzada):
        errors = [1 - score for score in cross_val_score(clasificador.clasificadorKNN, x, y, cv=particionado.repetitions)]
    else:
        errors = []
        for _ in range(particionado.repetitions):
          x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=particionado.test_size)
          self.entrenamiento(np.concatenate((x_train, np.transpose([y_train])), axis=1))
          predictions = self.clasifica(x_test)
          errors.append(super().error(y_test, predictions))
    return errors
  
  
class ClasificadorRegresionLogistica(Clasificador):
  def __init__(self, n_epochs, C=1, normalize=True):
    self.n_epochs = n_epochs
    self.C = C
    self.normalize = normalize
  
  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,):
    num_atributes = datosTrain.shape[1] - 1
    self.weights = [random.random() - 0.5 for _ in range(num_atributes + 1)]
    x_train = datosTrain[:,:-1]
    y_train = datosTrain[:,-1]
    
    self.means_and_desvs = calcularMediasDesv(x_train, nominalAtributos)
    if self.normalize == True:
      normalizarDatos(x_train, self.means_and_desvs, nominalAtributos)
    
    ones = np.ones((x_train.shape[0], 1))
    x_train = np.concatenate((ones, x_train), axis=1)
    
    for _ in range(self.n_epochs):
      for i, data_case in enumerate(x_train):
        prob = round(np.matmul(self.weights, np.transpose(data_case)), 2)
        try:
          prob = round(1 / (1 + math.exp(-prob)), 2)
        except OverflowError:
          prob = 0.0
        self.weights -= round(self.C * (prob - y_train[i]), 2) * data_case

  def clasifica(self,datosTest,nominalAtributos=None,diccionario=None,getProbabilities=False):    
    if self.normalize == True:
      normalizarDatos(datosTest, self.means_and_desvs, nominalAtributos)
      
    ones = np.ones((datosTest.shape[0], 1))
    datosTest = np.concatenate((ones, datosTest), axis=1)
      
    predictions = []
    probabilities = []
    for test_case in datosTest:
      prob = np.matmul(self.weights, np.transpose(test_case))
      try:
        prob = 1 / (1 + math.exp(-prob))
      except OverflowError:
        prob = 0.0
      probabilities.append(prob)
      predictions.append(0 if prob < 0.5 else 1)
    
    if getProbabilities == True:
      return probabilities
    return predictions

class ClasificadorRegresionLogistica_SK(Clasificador):
  def __init__(self, clasificador, normalize=True):
    self.normalize = normalize
    self.clasificadorReLog = clasificador

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,):
    self.datosTrain = np.array(datosTrain)
    self.means_and_desvs = calcularMediasDesv(self.datosTrain[:,:-1], nominalAtributos)
    if self.normalize == True:
      normalizarDatos(self.datosTrain[:,:-1], self.means_and_desvs, nominalAtributos)
    x_train = self.datosTrain[:,:-1]
    y_train = self.datosTrain[:,-1]
    self.clasificadorReLog.fit(x_train, y_train)
    
  def clasifica(self,datosTest,nominalAtributos=None,diccionario=None,getProbabilities=False):
    if self.normalize == True:
      normalizarDatos(datosTest, self.means_and_desvs, nominalAtributos)
    return self.clasificadorReLog.predict(datosTest)

  def validacion(self, particionado, dataset, clasificador, seed=None, ):
    x = dataset.datos[:,:-1]
    y = dataset.datos[:,-1]
    if isinstance(particionado, ValidacionCruzada):
        errors = [1 - score for score in cross_val_score(clasificador.clasificadorKNN, x, y, cv=particionado.repetitions)]
    else:
        errors = []
        for _ in range(particionado.repetitions):
          x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=particionado.test_size)
          self.entrenamiento(np.concatenate((x_train, np.transpose([y_train])), axis=1))
          predictions = self.clasifica(x_test)
          errors.append(super().error(y_test, predictions))
    return errors


class ClasificadorGenetico(Clasificador):
  def __init__(self, populationSize=25, numGenerations=50, maxRules=5, mutProb=0.05, elitismo=0.05, parents=0.5):
    self.populationSize = populationSize if populationSize >= 2 else 2
    self.numGenerations = numGenerations if numGenerations > 0 else 1
    self.maxRules = maxRules if maxRules > 0 else 1
    self.mutProb = mutProb if 0 <= mutProb <= 1 else 0.01
    self.elitismo = elitismo if elitismo < 1 else 0.05
    self.parents = int(((populationSize * parents) // 2) * 2) if populationSize > 2 and parents < 1 else 2
    

  def __genera_poblacion(self):
    population = []
    for _ in range(self.populationSize):
      individual = set() # Set para evitar reglas repetidas
      for _ in range(random.randrange(1, self.maxRules + 1)):
        while True:
          rule = ""
          for _ in range(self.ruleSize): # Regla aleatoria
            rule += random.choice("01")
          checkRule = rule[:-1].count("1")
          if not (checkRule == self.ruleSize - 1 or checkRule == 0):
            break
        individual.add(rule)
      population.append([list(individual), 0]) # Pasamos a lista para poder usar la seleccion por indice
    return np.array(population, dtype=object)


  def __convertir_datos(self, dataSinConvert, nominalAtributos):
    datos = []
    for dataCase in dataSinConvert:
      dataConvert = ""
      for atribIndex, atribValue in enumerate(dataCase):
        # Ponemos a 1 el bit del valor del atributo segun esta posicionado en el diccionario
        if nominalAtributos[atribIndex] is False:
          atrib = list(self.dicc.keys())[atribIndex]
          if atribValue in self.dicc[atrib]:
            atribValue = self.dicc[atrib][str(atribValue)]
            dataConvert += "0" * int(atribValue) + "1" + "0" * int(self.numValuesAtributes[atribIndex] - (atribValue + 1))
          else:
            dataConvert += "0" * self.numValuesAtributes[atribIndex]
        else:
          dataConvert += "0" * int(atribValue) + "1" + "0" * int(self.numValuesAtributes[atribIndex] - (atribValue + 1))
      datos.append(dataConvert)
    return datos


  def __calcular_fitnesses(self, population, dataTrain):
    for individual in population:
      fitnessIndiv = 0
      for data in dataTrain:
        predicts = {}
        for rule in individual[0]:
          isActivated = True
          index = 0
          for size in self.numValuesAtributes: # Convertimos a binario por atributo y comprobamos activacion
            binaryRule = int(rule[index:index+size], 2)
            binaryData = int(data[index:index+size], 2)
            if binaryRule & binaryData == 0:  # Algun atributo de la regla no se activa
              isActivated = False
              break
            index += size
          if isActivated: # Regla valida, apuntamos su prediccion
            if rule[-1] not in predicts.keys():
              predicts[rule[-1]] = 1
            else:
              predicts[rule[-1]] += 1
        if len(predicts.keys()) != 0:
          predict = max(predicts, key=predicts.get) # Guardamos la clase mas votada
          # No permitimos que haya varias clases con mayoria, evitamos aleatoriedad en decisiones
          if list(predicts.values()).count(predicts[predict]) == 1 and predict == data[-1]:
            fitnessIndiv += 1
      individual[1] = fitnessIndiv
    
    totalHits = sum(population[:,1])
    for i in range(len(population)):
      population[i][1] /= totalHits
    return population


  def __recombinacion(self, population):
    chosen = []
    while len(chosen) < self.parents and sum(population[:,1]) != 0: # Elegimos a los progenitores
      roulette = random.random()
      i = -1
      while roulette > 0:
        i += 1
        roulette -= population[i][1]
      if i not in chosen:
        chosen.append(i)
    
    for i in range(0, len(chosen), 2):
      ruleParent1 = random.randint(0, len(population[chosen[i]][0])-1)
      ruleParent2 = random.randint(0, len(population[chosen[i+1]][0])-1)
      if random.random() < 0.5: # Intra-rules
        #print("Intra")
        while(True):
          crossPoint = random.randint(0, self.ruleSize - 1)
          ruleChild1 = population[chosen[i]][0][ruleParent1][:crossPoint] + population[chosen[i+1]][0][ruleParent2][crossPoint:]
          ruleChild2 = population[chosen[i+1]][0][ruleParent2][:crossPoint] + population[chosen[i]][0][ruleParent1][crossPoint:]
          
          checkChild1, checkChild2 = ruleChild1[:-1].count("1"), ruleChild2[:-1].count("1")
          #si no se cumple que son todo 1 o 0 en alguna regla repito el cruce hasta que 
          if not (checkChild1 == self.ruleSize - 1 or checkChild1 == 0 \
            or checkChild2 == self.ruleSize - 1 or checkChild2 == 0):
            break

      else: # Inter-rules
        #print("Inter")
        ruleChild1, ruleChild2 = population[chosen[i+1]][0][ruleParent2], population[chosen[i]][0][ruleParent1]

      population[chosen[i]][0][ruleParent1], population[chosen[i+1]][0][ruleParent2] = ruleChild1, ruleChild2
    
    #print("Hijos:", chosen)

    return population

  
  def __mutacion(self, population):
    selectMutacion = random.random()
    
    if 0 <= selectMutacion < 0.25:      # Mutacion estandar a una regla de cada individuo
      for individual in population:
        ruleIndex = random.randint(0, len(individual[0])-1)
        while True:
          newRule = ""
          for bit in individual[0][ruleIndex]:
            if self.mutProb >= random.random():
              newRule += "0" if bit == "1" else "1"
            else:
              newRule += bit
          checkRule = newRule[:-1].count("1") 
          if not (checkRule == self.ruleSize - 1 or checkRule == 0):
              break
        individual[0][ruleIndex] = newRule

    elif 0.25 <= selectMutacion < 0.5:  # Mutacion estandar a todas las reglas de cada individuo
      for individual in population:
        for i in range(len(individual[0])):
          while True:
            newRule = ""
            for bit in individual[0][i]:
              if self.mutProb >= random.random():
                newRule += "0" if bit == "1" else "1"
              else:
                newRule += bit
            checkRule = newRule[:-1].count("1")
            #si no se cumple que son todo 1 o 0 en alguna regla repito el cruce hasta que 
            if not (checkRule == self.ruleSize - 1 or checkRule == 0):
              break
          individual[0][i] = newRule
    
    elif 0.5 <= selectMutacion < 0.75:  # Mutacion añadiendo una regla aleatoria a cada individuo
      for individual in population:
        if len(individual[0]) < self.maxRules and self.mutProb >= random.random():
          while True:
            rule = ""
            for _ in range(self.ruleSize):
              rule += random.choice("01")
            checkRule = rule[:-1].count("1")
            #si no se cumple que son todo 1 o 0 en alguna regla repito el cruce hasta que 
            if not (checkRule == self.ruleSize - 1 or checkRule == 0):
              break
          individual[0].append(rule)

    else:                               # Mutacion eliminando una regla a cada individuo
      for individual in population:
        if len(individual[0]) > 1 and self.mutProb >= random.random():
          individual[0].pop(random.randint(0, len(individual[0])-1))

    return population


  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None):
    self.numValuesAtributes = []
    self.dicc = {}

    #vemos los bits de cada parte de la regla
    for index, key in enumerate(list(diccionario.keys())[:-1]):
      numValues = len(diccionario[key].values())
      if numValues == 0: # Si es de tipo numérico
        values_set = [str(value) for value in sorted(set(datosTrain[:,index]))]
        numValues = len(values_set)
        self.dicc[key] = dict(zip(values_set, range(0, numValues)))
      else:
        self.dicc[key] = diccionario[key]
      self.numValuesAtributes.append(numValues)

    self.ruleSize = sum(self.numValuesAtributes) + 1

    population = self.__genera_poblacion()
    #print("Poblacion inicial:", population, "\n")

    dataTrain = self.__convertir_datos(datosTrain[:,:-1], nominalAtributos)
    dataTrain = [dataTrain[i] + str(value) for i, value in enumerate(datosTrain[:,-1])]
    #print("Datos de entrenamiento:", datosTrain, "\n")

    self.fitnesses = np.empty((self.numGenerations, 2))
    for i in range(self.numGenerations):
      #print("\nGeneracion %d:\n" % i)
      population = self.__calcular_fitnesses(population, dataTrain)
      #print("Fitnesses:", population, "\n")

      # Ordenamos la poblacion por fitness descendente
      population = population[(-1*population)[:,1].argsort()]

      self.fitnesses[i][0] = population[0][1] # Guardamos el fitness del mejor individuo
      self.fitnesses[i][1] = np.mean(population[:,1]) # Guardamos el fitness medio de la generacion

      # Si encontramos al individuo perfecto, acabo la busqueda
      if population[0][1] == 1:
        self.individuo = population[0]
        return

      numElites = int(self.populationSize * self.elitismo)
      elites = [copy.deepcopy(individual) for individual in population[:numElites]]
      #print("Individuos de la elite:", elites, "\n")
     
      positiveFitnesses = 0
      for fitness in population[:,1]:
        positiveFitnesses += 1 if fitness != 0 else 0
      if positiveFitnesses < 2:
        sys.exit("La población no ha sobrevivido")

      population = self.__recombinacion(population)
      #print("Poblacion tras recombinacion:", population, "\n")
      
      population = self.__mutacion(population)
      #print("Poblacion tras mutacion:", population, "\n")

      # Reemplazo
      if len(elites) != 0:
        population = population[:-len(elites)]
        population = np.append(population, elites, 0)
      #print("Poblacion con la elite:", population, "\n")

    # Al terminar de entrenar nos quedamos con el mejor individuo
    population = self.__calcular_fitnesses(population, dataTrain)
    self.individuo = population[np.argmax(population[:,1])]
    

  def clasifica(self,datosTest,nominalAtributos=None,diccionario=None,getProbabilities=False):
    predictions = []

    if not bool(self.dicc) and not bool(self.individuo): # Comprueba si hemos entrenado
      return None

    dataTest = self.__convertir_datos(datosTest, nominalAtributos)
    #print("Convertir datos: ", dataTest[0])
    
    for data in dataTest:
      predicts = {}
      for rule in self.individuo[0]:
        isActivated = True
        index = 0
        for size in self.numValuesAtributes: # Convertimos a binario por atributo y comprobamos activacion
          binaryRule = int(rule[index:index+size], 2)
          binaryData = int(data[index:index+size], 2)
          if binaryRule & binaryData == 0:  # Algun atributo de la regla no se activa
            isActivated = False
            break
          index += size
        if isActivated: # Regla valida, apuntamos su prediccion
          if rule[-1] not in predicts.keys():
            predicts[rule[-1]] = 1
          else:
            predicts[rule[-1]] += 1
      if len(predicts.keys()) != 0: #si predice algo
        predict = max(predicts, key=predicts.get) # Guardamos la clase mas votada
        # No permitimos que haya varias clases con mayoria, evitamos aleatoriedad en decisiones
        if list(predicts.values()).count(predicts[predict]) == 1:
          predictions.append(int(predict))
        else:
          predictions.append(-1)
      else:
        predictions.append(-1)
    return predictions