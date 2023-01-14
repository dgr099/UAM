from abc import ABCMeta,abstractmethod
from random import random, sample
import math

class Particion():

  # Esta clase mantiene la lista de �ndices de Train y Test para cada partici�n del conjunto de particiones  
  def __init__(self, listTrain, listTest):
    self.indicesTrain=listTrain
    self.indicesTest=listTest

#####################################################################################################

class EstrategiaParticionado:
  
  # Clase abstracta
  __metaclass__ = ABCMeta
  
  repetitions = 0
  """Numero de repeticiones del bucle de entrenamiento"""
  test_size = 0
  """Porcentaje de tamaño de cada particion de test (entre 0 y 1)"""
  
  @abstractmethod
  def creaParticiones(self,datos,seed=None):
    pass
  

#####################################################################################################

class ValidacionSimple(EstrategiaParticionado):
  
  # Crea particiones segun el metodo tradicional de division de los datos segun el porcentaje deseado y el n�mero de ejecuciones deseado
  # Devuelve una lista de particiones (clase Particion)
  def creaParticiones(self,datos,seed=None):
    #random.seed(seed)
    data_rows = datos.shape[0] #filas del dataset
    tamTest = math.floor(data_rows * self.test_size) #numero de indices del test
    random_rows = sample(range(0, data_rows), data_rows) #indices de filas aleatorios
    return Particion(random_rows[tamTest:], random_rows[:tamTest]) #retorno la partición con lo calculado
  
  def __init__(self, reps, test_size):
    self.repetitions = reps
    self.test_size = test_size #tamaño (en porcentaje 0<=x<=1)
      
#####################################################################################################      
class ValidacionCruzada(EstrategiaParticionado):
  
  # Crea particiones segun el metodo de validacion cruzada.
  # El conjunto de entrenamiento se crea con las nfolds-1 particiones y el de test con la particion restante
  # Esta funcion devuelve una lista de particiones (clase Particion)
  def creaParticiones(self,datos,seed=None):   
    #random.seed(seed)
    data_rows = datos.shape[0]

    rows_partitions = []
    used_rows = 0
    for _ in range(self.repetitions):
      rows = math.floor(self.test_size * data_rows)
      rows_partitions.append(rows)
      used_rows += rows
      
    i = 0
    while used_rows != data_rows:
      rows_partitions[i] += 1
      used_rows += 1
      i = (i + 1) % len(rows_partitions)

    random_rows = sample(range(0, data_rows), data_rows)

    partitions = []
    used_size = 0
    for size in rows_partitions:
      partitions.append(Particion(random_rows[:used_size] + random_rows[used_size + size:],random_rows[used_size:used_size + size]))
      used_size += size

    return partitions
    
      
  def __init__(self, test_size):
    self.repetitions = int(1 // test_size)
    self.test_size = test_size
