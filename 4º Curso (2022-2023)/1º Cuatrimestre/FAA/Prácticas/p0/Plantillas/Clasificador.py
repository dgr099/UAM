from abc import ABCMeta,abstractmethod


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
  def clasifica(self,datosTest,nominalAtributos,diccionario):
    pass
  
  # Obtiene el numero de aciertos y errores para calcular la tasa de fallo
  def error(self,datos,pred):
    # Aqui se compara la prediccion (pred) con las clases reales y se calcula el error    
    comparations = list(np.bitwise_xor(pred, datos.columns[-1]))
    return comparations.count[0], comparations.count(1)
    
    # Con esto solo consigo los fallos, no las dos
    #return (datos.shape[0] - [pred[i] - datos[i][-1] for i in range(datos.shape[0])].count(0))
  
  # Realiza una clasificacion utilizando una estrategia de particionado determinada
  # TODO: implementar esta funcion
  def validacion(self,particionado,dataset,clasificador,seed=None):
    # Creamos las particiones siguiendo la estrategia llamando a particionado.creaParticiones
    # - Para validacion cruzada: en el bucle hasta nv entrenamos el clasificador con la particion de train i
    # y obtenemos el error en la particion de test i
    # - Para validacion simple (hold-out): entrenamos el clasificador con la particion de train
    # y obtenemos el error en la particion test. Otra opci�n es repetir la validaci�n simple un n�mero especificado de veces, obteniendo en cada una un error. Finalmente se calcular�a la media.
    pass  

##############################################################################

class ClasificadorNaiveBayes(Clasificador):
  def entrenamiento(self, datosTrain,nominalAtributos, diccionario):
      #Calculamos las probabilidades a priori de cada valor de clase P(c)
      index_h = datosTrain.shape[1]
      values_set = sorted(set(datosTrain[index_h]))
      last_column = datosTrain[:,-1]
      print(last_column)
      #for h in values_set: #para cada h contamos sus apariciones
        
      if(nominalAtributos[index_h] == True): #comprobamos que no sea nominal
        pass