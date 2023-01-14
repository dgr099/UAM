from Plantillas import Datos, EstrategiaParticionado, Clasificador#, Clasificador
import matplotlib.pyplot as plt
import numpy as np
from sklearn import metrics


from sklearn.naive_bayes import MultinomialNB as mnb
from Plantillas.Clasificador import ClasificadorNaiveBayesSk


def confMatrix(pred, datos):
    
    r"""Genera matriz de confusion"""
    hipotesis = len(sorted(set(datos[:,-1]))) # Posibles valores de la hipotesis ordenados

    matriz = np.zeros((hipotesis,hipotesis))

    clases = datos[:,-1]

    for i in range(hipotesis):
        clasei = clases == i

        for j in range(hipotesis):
            matriz[j,i] = sum(pred[clasei] == j)

    return matriz

def calculateValues(datos, pred):
    cMatrix = metrics.confusion_matrix(datos[:,-1], pred)
    #sorted(set(datos[:,-1])) Posibles valores de la hipotesis ordenados
    tp = 0
    fp = 0
    fn = 0
    tn = 0

    tPIndex=0
    tFIndex=1    
    nHipotesis = len(cMatrix)

    #recorro la matriz de confusión
    for index in range(nHipotesis):
        for index_2 in range(nHipotesis):
            if(index==tPIndex): #si estamos analizando la fila de los positives
                if(index==index_2): #si estamos en el punto de tp
                    tp+=cMatrix[index][index_2]
                else: #caso contrario estamos en fp
                    fp+=cMatrix[index][index_2]
            elif(index==tFIndex): #same caso anterior pero con los falses
                if(index==index_2):
                    tn+=cMatrix[index][index_2]
                else:
                    fn+=cMatrix[index][index_2]

    tpr = tp/(tp+fn)
    fnr = fn/(tp+fn)
    fpr=fp/(fp+tn)
    tnr=tn/(fp+tn)

    return [tpr, fnr, fpr, tnr]


def printRocSpace(datos):
    vSimple = EstrategiaParticionado.ValidacionSimple(1, 0.2)
    partitions = vSimple.creaParticiones(datos.datos)
    kVecinos = Clasificador.ClasificadorKNN(5)
    #nBayes = Clasificador.ClasificadorNaiveBayes()
    #nb de sklearn
    nBayes = ClasificadorNaiveBayesSk(mnb())
    rLineal = Clasificador.ClasificadorRegresionLogistica(5, 0.1)
    clasificadores = [kVecinos, nBayes, rLineal]
    colors = ['blue', 'red', 'green']
    clasificadoresStr=["kVecinos", "nBayes", "rLineal"]
    import matplotlib.patches as mpatches
    patchs=[]
    fig, ax = plt.subplots()
    for i in range(len(colors)):
        patchs.append(mpatches.Patch(color=colors[i], label=clasificadoresStr[i]))
    
        ax.legend(handles=patchs)
    for _ in range(vSimple.repetitions):
        partition = vSimple.creaParticiones(datos.datos)
        d_train = datos.extraeDatos(partition.indicesTrain)
        d_test = datos.extraeDatos(partition.indicesTest)
        for index, clasificador in enumerate(clasificadores):
            clasificador.entrenamiento(d_train, datos.nominalAtributos, datos.diccionarios, True)
            
            predictions = clasificador.clasifica(d_test[:, :-1], datos.nominalAtributos, datos.diccionarios)
            values = calculateValues(d_test, predictions)
            plt.plot(values[2], values[0], 'o', color=colors[index])
    plt.title("Rock Space")
    plt.xlabel("FPR or (1-specifity)")
    plt.ylabel("TPR or sensitivity")
    plt.show()

def printRocCurve(datos):
    vSimple = EstrategiaParticionado.ValidacionSimple(1, 0.2)
    partitions = vSimple.creaParticiones(datos.datos)
    rLineal = Clasificador.ClasificadorRegresionLogistica(5, 0.1)
    for _ in range(vSimple.repetitions):
        partition = vSimple.creaParticiones(datos.datos)
        d_train = datos.extraeDatos(partition.indicesTrain)
        d_test = datos.extraeDatos(partition.indicesTest)
        rLineal.entrenamiento(d_train, datos.nominalAtributos, datos.diccionarios, True)
        probs = rLineal.clasifica(d_test[:, :-1], datos.nominalAtributos, datos.diccionarios, getProbabilities=True)
        probs = [round(item, 3) for item in probs] #redondeamos a dos decimales todas las probabilidades
        probs = sorted(probs, reverse=True) #ordenamos
        hipotesis = sorted(set(datos.datos[:,-1])) # Posibles valores de la hipotesis ordenados
        n_1=0
        n_2=0
        aux=-1
        probSinRepetir = []
        hips = []
        for i in range(1, len(probs)):
            if aux != probs[i]:
                probSinRepetir.append(probs[i])
                hips.append(d_test[i][-1])
                if(d_test[i][-1] == hipotesis[0]):
                    n_1+=1
                else:
                    n_2+=1
                aux = probs[i]
        
        #probs = set(probs) #eliminamos repetidos
        probs=probSinRepetir
        #n_1 = np.count_nonzero(d_test[:,-1] == hipotesis[0])
        #n_2 = np.count_nonzero(d_test[:,-1] == hipotesis[1])
        y=0
        x=0
        x_arr =[]
        y_arr =[]
        #plt.plot(x, y, 'o')
        x_arr.append(x)
        y_arr.append(y)
        for i, prob in enumerate(probs):
            if(hips[i]==hipotesis[0]):
                y+=1/n_1
            elif(hips[i]==hipotesis[1]):
                x+=1/n_2
            x_arr.append(x)
            y_arr.append(y)
            plt.annotate(str(prob), xy=(x, y))
            

        #values = calculateValues(d_test, predictions, rLineal)
            #plt.plot(values[2], values[0], 'o', color=colors[index])
        plt.plot(x_arr, y_arr)
        plt.title("AUC Roc curve")
        plt.xlabel("FPR or (1-specifity)")
        plt.ylabel("TPR or sensitivity")
        #lt.scatter(x_arr, y_arr)
        plt.show()


