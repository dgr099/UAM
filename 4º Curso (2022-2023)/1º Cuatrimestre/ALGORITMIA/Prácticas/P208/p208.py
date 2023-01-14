import numpy as np
import itertools
from typing import List, Dict

"""
Autores:
    Daniel Cerrato Sánchez (daniel.cerrato@estudiante.uam.es)
    David T. Garitagoitia Romero (david.garitagoitia@estudiante.uam.es)
"""

def init_cd(n:int) -> np.ndarray:
    """Metodo que inicializa un array de tamano 'n' con valores
    
        ARGS:
            n (int): Tamano del array

        RETURNS:
            np.ndarray: Array numpy de tamano 'n' inicializado a -1
                en todas sus posiciones
    """

    return np.array([-1 for _ in range(n)])


def union(rep_1: int, rep_2: int, p_cd: np.ndarray)-> int:
    """Metodo que une dos conjuntos por rangos y devuelve el representante 
        del conjunto final
        
        ARGS:
            rep_1 (int): indice del representante del conjunto 1
            rep_2 (int): indice del representante del conjunto 2
            p_cd (np.ndarray): array de conjuntos disjuntos
            
        RETURNS:
            int: indice del representante del conjunto unido"""

    if p_cd is None:
        return None
    if (p_cd[rep_1] < p_cd[rep_2]): #caso 1º con mayor rango
       p_cd[rep_2] = rep_1 #2º cuelga del 1º
       return rep_1
    elif (p_cd[rep_1] == p_cd[rep_2]): #caso mismo de rango
        p_cd[rep_2] = rep_1 #el 2º cuelga del 1º
        p_cd[rep_1] -= 1 #aumenta el rango del 1º
        return rep_1
    else: #caso 2º con más rango
        p_cd[rep_1] = rep_2 #1º cuelga del 2º
        return rep_2


def find(ind: int, p_cd: np.ndarray)-> int:
    """Metodo que busca el representante del indice recibido en su conjunto disjunto
    
        ARGS:
            ind (int): indice del nodo a buscar
            p_cd (np.ndarray): array de conjuntos disjuntos
            
        RETURNS:
            int: indice del representante del conjunto disjunto al que pertenece
                el indice dado"""

    if p_cd is None:
        return None
    ind_medio = []
    while(p_cd[ind] >= 0): # hasta nodo padre
        ind_medio.append(ind)
        ind = p_cd[ind] #comprueba al padre
    # Compresion de caminos
    while(len(ind_medio) > 0):
        p_cd[ind_medio.pop()] = ind
    return ind


def cd_2_dict(p_cd: np.ndarray)-> Dict:
    """Metodo que convierte un array de conjuntos disjuntos en
        un diccionario de conjuntos disjuntos
        
        ARGS:
            p_cd (np.ndarray): array de conjuntos disjuntos
            
        RETURNS:
            Dict: Diccionario de conjuntos disjuntos indexados
                por el representante del conjunto"""

    if p_cd is None:
        return None
    dict = {}
    for i in range(len(p_cd)):
        repr_val = find(i, p_cd)
        if(repr_val not in dict.keys()):
            dict[repr_val] = [i]
        else:
            dict[repr_val].append(i)
    return dict


def ccs(n: int, l: List)-> Dict:
    """Metodo que devuelve las componentes conexas del grafo dado como lista
    
        ARGS:
            n (int): numero de vertices del grafo
            l (List): lista de ramas del grafo
            
        RETURNS:
            Dict: diccionario que contiene las componentes conexas del grafo"""
            
    cd = init_cd(n)
    for branch in l:
        rep_A = find(branch[0], cd) #representante del vertice A de la rama
        rep_B = find(branch[1], cd) #representante del vertice B de la rama
        if(rep_A != rep_B): #si tienen distintos representantes son de distintos conjuntos
            union(rep_A, rep_B, cd)
    return cd_2_dict(cd)


def dist_matrix(n_nodes: int, w_max=10)-> np.ndarray:
    """Metodo que genera una matriz de distancias de un grafo
        
        ARGS:
            n_nodes (int): numero de nodos del grafo
            w_max (int): valor maximo de las distancias del grafo. Por defecto coste 10

        RETURNS:
            np.ndarray: Matriz de distancias bidimensional y cuadrada de tamano n_nodes"""

    dist_matrix = np.random.randint(1, high=w_max, size=(n_nodes, n_nodes))
    dist_matrix = (dist_matrix + np.transpose(dist_matrix)) // 2
    np.fill_diagonal(dist_matrix, 0)
    return dist_matrix
    

def greedy_tsp(dist_m: np.ndarray, node_ini=0)-> List:
    """Metodo que calcula un circuito codicioso a través del grafo empezando por
        un nodo inicial dado en base al camino menos costoso

        ARGS:
            dist_m (np.ndarray): matriz de distancias entre nodos del grafo
            node_ini (int): indice del nodo de partida. Por defecto indice 0

        RETURNS:
            List: lista con el orden de los nodos que forman el circuito codicioso"""

    num_cities = dist_m.shape[0]
    circuit = [node_ini]
    # Para cada ciudad cogemos el camino menos costoso a una ciudad no visitada
    while len(circuit) < num_cities:
        current_city = circuit[-1]
        sorted_cities = list(np.argsort(dist_m[current_city]))
        for city in sorted_cities:
            if city not in circuit:
                circuit.append(city)
                break
    return circuit + [node_ini]


def len_circuit(circuit: List, dist_m: np.ndarray) -> int:
    """Metodo que calcula el coste de un circuito codicioso a traves de su matriz de distancias

        ARGS:
            circuit (List): lista con el orden de los indices de los nodos visitados en el circuito
            dist_m (np.ndarray): matriz de distancias entre nodos del grafo

        RETURNS:
            List: lista con el orden de los nodos que forman el circuito codicioso"""
    
    num_cities = dist_m.shape[0]
    distance = 0 
    for i in range(num_cities):  # En un circuito hay el mismo numero de caminos que ciudades
        distance += dist_m[circuit[i]][circuit[i+1]]
    return distance 


def repeated_greedy_tsp(dist_m: np.ndarray) -> List:
    """Metodo que utiliza la función greedy_tsp empezando en cada nodo

        ARGS:
            dist_m (np.ndarray): matriz de distancias entre nodos del grafo

        RETURNS:
            List: Devuelve el circuito codicioso de menor coste"""
            
    min_distance = -1
    for node in range(dist_m.shape[0]):
        candidate_circuit = greedy_tsp(dist_m, node)
        candidate_distance = len_circuit(candidate_circuit, dist_m)
        if candidate_distance < min_distance or min_distance == -1:
            greedy_circuit, min_distance = candidate_circuit, candidate_distance
    return greedy_circuit


def exhaustive_tsp(dist_m:np.ndarray) -> List:
    """Genera todas las permutaciones posibles de las ciudades o de los nodos y examina todas las permutaciones

        ARGS:
            dist_m (np.ndarray): matriz de distancias entre nodos del grafo

        RETURNS:
            List: Devuelve el circuito codicioso de menor coste"""
    
    cities = list(range(dist_m.shape[0]))
    min_dist = -1 # Iniciado a -1 para forzar que entre en el if mínimo una vez
    for perm in itertools.permutations(cities): 
        candidate_circuit = list(perm) + [perm[0]] 
        candidate_distance = 0
        for i in range(len(perm)): # En un circuito hay el mismo numero de caminos que ciudades
            candidate_distance += dist_m[candidate_circuit[i]][candidate_circuit[i+1]]
        if min_dist > candidate_distance or min_dist == -1:
            min_dist, min_circ = candidate_distance, candidate_circuit
    return min_circ

"""
if __name__ == "__main__":

    # Pruebas de find
    p_cd = [-4, 0, 5, 1, 0, 4]
    assert find(2, p_cd) == 0
    assert p_cd == [-4, 0, 0, 1, 0, 0]

    # Pruebas de union
    p_cd = [2, -2, -2, 1] # caso rangos iguales
    assert union(2, 1, p_cd) == 2
    assert p_cd == [2, 2, -3, 1]
    p_cd = [2, -1, -2] # caso primero mayor
    assert union(2, 1, p_cd) == 2
    assert p_cd == [2, 2, -2]
    p_cd = [1, -2, -1] # caso segundo mayor
    assert union(2, 1, p_cd) == 1
    assert p_cd == [1, -2, 1]

    # Pruebas de cd_2_dict
    p_cd = [2, -2, -2, 1]
    final_dict = {1: [1, 3], 2: [0, 2]}
    assert cd_2_dict(p_cd) == final_dict

    # Pruebas de ccs
    l = list([(0, 3), (1, 2), (1, 4), (4, 5), (5, 6), (4, 6)])
    final_dict = {0 : [0, 3], 1 : [1, 2, 4, 5, 6]}
    assert ccs(7, l) == final_dict

    # Pruebas de dist_matrix
    size, v_max = 5, 10
    matrix = dist_matrix(size, v_max)
    assert matrix.shape == (size, size)
    for i in range(matrix.shape[0]):
        for j in range(i, matrix.shape[1]):
            if i == j:
                assert matrix[i][j] == 0
            else:
                assert matrix[i][j] <= v_max
                assert matrix[i][j] == matrix[j][i]

    # Pruebas de greedy_tsp
    matrix = np.array([[0, 624, 506, 357],
                       [624, 0, 995, 350],
                       [506, 995, 0, 653],
                       [357, 350, 653, 0]])
    best_way = [0, 3, 1, 2, 0]
    circuito = greedy_tsp(matrix, 0)
    assert best_way == circuito

    # Pruebas de len_circuit
    assert len_circuit(circuito, matrix) == 2208

    # Pruebas de repeated_greedy_tsp
    assert repeated_greedy_tsp(matrix) == [3, 1, 0, 2, 3]

    # Pruebas de exhaustive_tsp
    assert exhaustive_tsp(matrix) == [0, 1 , 3 , 2, 0]

    print("Test Perfecto")
"""