# -*- coding: utf-8 -*-

# coding: utf-8
import pandas as pd
import numpy as np

"""
Autores:
    Daniel Cerrato Sánchez (daniel.cerrato@estudiante.uam.es)
    David T. Garitagoitia Romero (david.garitagoitia@estudiante.uam.es)
"""
class Datos:
    """Clase que contiene los datos de un dataset desglosados"""

    datos = np.empty([])
    """Array bidimensional con los datos del dataset en formato numerico."""
    
    diccionarios = {}
    """Diccionario de diccionarios donde se guarda la relacion entre
        los atributos nominales y el valor numerico que ocupan en 'datos'.
        Los atributos numericos contienen un diccionario vacio."""
        
    nominalAtributos = []
    """Lista de booleanos que indican si el atributo es nominal o no."""

    def __init__(self, nombreFichero):
      """Constructor de la clase que inicializa los atributos de la clase desglosando
            el dataset recibido por argumento"""
      
      dataframe = pd.read_csv(nombreFichero)
      df_types = dataframe.dtypes

      # Bucle que se encarga de crear los atributos 'diccionarios' y 'nominalAtributos'
      for key in df_types.keys():
        self.diccionarios[key] = {}
        
        if df_types[key] == "object":
          self.nominalAtributos.append(True)
          values_set = sorted(set(dataframe[key]))
          
          # Sentencia que añade a 'diccionarios' un diccionario de pares 
          # {atributo nominal: valor numerico (index)}
          # a traves de la compresion (fusion) de listas
          self.diccionarios[key] = dict(zip(values_set, range(1, len(values_set) + 1)))
          
          # Version extendida de la sentencia anterior
          #for i, value in enumerate(values_set):
          #  self.diccionarios[key][value] = i
            
        else:
          self.nominalAtributos.append(False)    
        
      # Sentencia que cambia los valores nominales por su valor numerico correspondiente
      self.datos = np.array(dataframe.replace(self.diccionarios))

    # Devuelve el subconjunto de los datos cuyos �ndices se pasan como argumento
    def extraeDatos(self, idx):
      #return [self.datos[row] for row in idx]
      return self.datos[idx]
