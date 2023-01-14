from Plantillas import Datos, EstrategiaParticionado, Clasificador

dataPath = './ConjuntosDatosIntroFAA/'

dataset = Datos.Datos(dataPath + "german.csv")

dataset=Datos.Datos(dataPath + 'tic-tac-toe.csv')
estrategiaS = EstrategiaParticionado.ValidacionSimple(10, 0.2)
clasificador=Clasificador.ClasificadorNaiveBayes()
clasificador.entrenamiento(dataset.datos, dataset.nominalAtributos, dataset.diccionarios)