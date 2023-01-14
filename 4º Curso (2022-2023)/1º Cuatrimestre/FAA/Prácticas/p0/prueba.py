from Plantillas import Datos, EstrategiaParticionado#, Clasificador

dataPath = './ConjuntosDatosIntroFAA/'

dataset1 = Datos.Datos(dataPath + "german.csv")
print(dataset1.datos)

dataset2 = Datos.Datos(dataPath + 'tic-tac-toe.csv')
print(dataset2.datos)

estrategia = EstrategiaParticionado.ValidacionCruzada(0.1)
print("Repeticiones:", estrategia.repetitions)
print("Tamano de la prueba:", estrategia.test_size)
for partition in estrategia.creaParticiones(dataset1.datos):
    print("TRAIN")
    print(partition.indicesTrain)
    print("TEST")
    print(partition.indicesTest)
estrategiaS = EstrategiaParticionado.ValidacionSimple(10, 0.2)
print("Repeticiones:", estrategiaS.repetitions)
print("Tamano de la prueba:", estrategiaS.test_size)
partition = estrategiaS.creaParticiones(dataset1.datos)
print("TRAIN")
print(partition.indicesTrain)
print("TEST")
print(partition.indicesTest)