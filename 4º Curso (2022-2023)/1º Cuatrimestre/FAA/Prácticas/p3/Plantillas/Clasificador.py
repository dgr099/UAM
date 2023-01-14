from abc import ABCMeta, abstractmethod
from collections import Counter
import random
import numpy as np
import pandas as pd
import math
from sklearn.exceptions import ConvergenceWarning

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
  def validacion(self,particionado,dataset,clasificador,seed=None, laplace=True):
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
      clasificador.entrenamiento(d_train, dataset.nominalAtributos, dataset.diccionarios, laplace)
      predictions = clasificador.clasifica(d_test[:, :-1], dataset.nominalAtributos, dataset.diccionarios)
      errors.append(clasificador.error(d_test[:,-1], predictions))
    return errors



class ClasificadorNaiveBayes(Clasificador):

  def entrenamiento(self, datosTrain, nominalAtributos, diccionario=None, laplace=True):
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
          if zero_flag == 1 and laplace:
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
      
  def entrenamiento(self, datosTrain, nominalAtributos=None, diccionario=None, laplace=True):
    x_train = datosTrain[:,:-1]
    y_train = datosTrain[:,-1]
    self.metodoNB.fit(x_train, y_train)
    
  def clasifica(self, datosTest, nominalAtributos=None, diccionario=None,getProbabilities=False):
    return self.metodoNB.predict(datosTest)
  
  def validacion(self, particionado, dataset, clasificador, seed=None, laplace=True):
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

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,laplace=True):
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

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,laplace=True):
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

  def validacion(self, particionado, dataset, clasificador, seed=None, laplace=True):
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
  
  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,laplace=True):
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

  def entrenamiento(self,datosTrain,nominalAtributos=None,diccionario=None,laplace=True):
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

  def validacion(self, particionado, dataset, clasificador, seed=None, laplace=True):
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