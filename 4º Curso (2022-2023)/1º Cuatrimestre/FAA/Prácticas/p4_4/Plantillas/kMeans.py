"""
el objetivo del K-Means es minimizar la suma de las distancias 
entre los puntos y el centroide al que pertenecen
"""
import random
import numpy as np
from sklearn import metrics
import matplotlib.pyplot as plt


def classesCluster(datos, clusters):
    classes = []
    for cluster in clusters:
        classes_cluster = []
        for case_index in cluster:
            classes_cluster.append(datos[case_index][-1])
        # Guardamos la clase más común del cluster
        classes.append(max(classes_cluster, key=classes_cluster.count))
    return classes

def checkClusters(datos, clusters):
    classes = classesCluster(datos, clusters)
    pred = [0] * datos.shape[0]
    real_classes = [0] * datos.shape[0]
    for i in range(len(classes)):
        for ind in clusters[i]:
            pred[ind] = classes[i]
            real_classes[ind] = datos[ind][-1]
    return pred

def getConfusionMatrix(real_classes, pred):
    confusion_matrix = metrics.confusion_matrix(real_classes, pred)
    cm_display = metrics.ConfusionMatrixDisplay(confusion_matrix=confusion_matrix)
    cm_display.plot()
    plt.show()

class kMeans:
    def __init__(self, k):
        self.k = k

    def clasifica(self, datos):
        if self.k < 0:
            return

        clusters = []
        num_cases = datos.shape[0]
        num_atributes = datos.shape[1] - 1

        if self.k > num_cases:
            self.k = num_cases

        centroids = random.sample(range(num_cases), self.k)
        for i in range(self.k):
            clusters.append([])
            centroids[i] = datos[centroids[i]]
        # El indice del centroide es el cluster al que pertenece

        for i in range(num_cases):
            clusters[0].append(i)

        # Asignamos cada punto a su centroide más cercano
        criterio_conv = False
        while criterio_conv == False:

            criterio_conv = True

            for cluster_index in range(self.k):
                num_elements = len(clusters[cluster_index])
                
                elem_index = 0
                while elem_index < num_elements: # Recorremos todos los elementos del cluster
                    case_index = clusters[cluster_index][elem_index] # Indice en la matriz 'datos'
                    case = datos[case_index]
                    
                    euclidean_distances = np.zeros(self.k)
                    for i in range(self.k):              
                        for atrib_index in range(num_atributes):
                            euclidean_distances[i] += (centroids[i][atrib_index] - case[atrib_index])**2
                    
                    # Comprobamos si hay un centroide mas cercano. Si es asi, le reasignamos a ese cluster
                    nearest_cluster = np.argmin(euclidean_distances)
                    if nearest_cluster != cluster_index:
                        clusters[cluster_index].remove(case_index)
                        clusters[nearest_cluster].append(case_index)
                        elem_index -= 1     # La extracción obliga a disminuir el indice actual
                        num_elements -= 1   # y el numero de elementos del cluster
                        criterio_conv = False # No se cumple criterio de convergencia, volveremos a comprobar todos
                    
                    elem_index += 1

            if criterio_conv == False: # Cambiamos los centroides
                for i in range(self.k):
                    new_centroid = np.zeros(num_atributes + 1)
                    for case_index in clusters[i]:
                        new_centroid += datos[case_index] # Suma elemento a elemento por ser ndarray
                    new_centroid /= len(clusters[i]) # Con los valores medios de cada atributo
                    centroids[i] = new_centroid
                    
        return checkClusters(datos, clusters)