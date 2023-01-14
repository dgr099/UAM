import numpy as np
import itertools

from typing import List, Tuple, Dict, Callable, Iterable, Union

"""
Autores:
    Daniel Cerrato Sanchez (daniel.cerrato@estudiante.uam.es)
    David T. Garitagoitia Romero (david.garitagoitia@estudiante.uam.es)
"""

def split(t: np.ndarray)-> Tuple[np.ndarray, int, np.ndarray]:
    """Funcion que divide la tabla t entre dos subtablas con los elementos menores y mayores
        que el valor en primera posicion (pivote)
        
        ARGS:
            t (np.ndarray): tupla a dividir en funcion del pivote
            
        RETURNS:
            np.ndarray: tupla de elementos menores al pivote
            int: pivote
            np.ndarray: tupla de elementos mayores al pivote 
    """            
    lower_list, bigger_list = [], []
    pivot = t[0]
    for value in t[1:]: # t[0] ya esta cogido
        if pivot > value:
            lower_list.append(value)
        elif pivot < value:
            bigger_list.append(value)

    return np.array(lower_list), pivot, np.array(bigger_list)


def qsel(t: np.ndarray, k:int)-> Union[int, None]:
    """Funcion recursiva del algoritmo QuickSelect, el cual devuelve el valor de un elemento
            dada su posicion en una tabla si esta estuviera ordenada
        
        ARGS:
            t (np.ndarray): tabla numerica en la que se buscara el elemento en posicion dada
            k (int): posicion del elemento a encontrar en la tabla ordenada
            
        RETURNS:
            int: valor del elemento en la tabla ordenada o None en caso de no encontrarlo
    """
    if k < 0 or k >= len(t):
        return None

    lower_list, pivot, bigger_list = split(t)
    
    pos_pivot = len(lower_list)
    if pos_pivot > k: #comprobamos si el elemento esta en la lista menor
        return qsel(lower_list, k) 
    elif pos_pivot == k:
        return pivot
    else:
        return qsel(bigger_list, k - (pos_pivot + 1))


def qsel_nr(t: np.ndarray, k: int)-> Union[int, None]:
    """Funcion iterativa del algoritmo QuickSelect, el cual devuelve el valor de un elemento
            dada su posicion en una tabla si esta estuviera ordenada
        
        ARGS:
            t (np.ndarray): tabla numerica en la que se buscara el elemento en posicion dada
            k (int): posicion del elemento a encontrar en la tabla ordenada
            
        RETURNS:
            int: valor del elemento en la tabla ordenada o None en caso de no encontrarlo
    """
    if k < 0 or k >= len(t):
        return None
    
    while True:
        lower_list, pivot, bigger_list = split(t)
    
        pos_pivot = len(lower_list)
        if pos_pivot > k: #comprobamos si el elemento esta en la lista menor
            t = lower_list
        elif pos_pivot == k:
            return pivot
        else:
            t = bigger_list
            k -= pos_pivot + 1


def split_pivot(t: np.ndarray, mid: int)-> Tuple[np.ndarray, int, np.ndarray]:
    """Funcion que divide la tabla t entre dos subtablas con los elementos menores y mayores
        que el valor en la posicion dada (pivote)
        
        RGS:
            t (np.ndarray): tupla a dividir en funcion del pivote
            mid (int): indice del valor que actuara como pivote
            
        RETURNS:
            np.ndarray: tupla de elementos menores al pivote
            int: pivote
            np.ndarray: tupla de elementos mayores al pivote 
    """  
    lower_list, bigger_list = [], []
    pivot = mid
    for value in t:
        if pivot > value:
            lower_list.append(value)
        elif pivot < value:
            bigger_list.append(value)

    return np.array(lower_list), pivot, np.array(bigger_list)


def pivot5(t: np.ndarray)-> int:
    """Funcion que devuelve el pivote de una tabla dada de acuerdo al procedimiento “mediana de medianas
        de 5 elementos”.

        ARGS:
            t (np.ndarray): tabla de la que se desea obtener el pivote
            
        RETURNS:
            int: valor de la mediana de la tabla (pivote)
    """         
    medians = []
    for i in range(0, len(t), 5):
        aux_list = t[i:i+5]
        aux_list.sort()
        aux_list_len = len(aux_list)
        # Cogemos la mediana o el izquierdo de la mediana en caso de longitud par
        medians.append(aux_list[(aux_list_len - 1) // 2])
    
    medians.sort()
    medians_len = len(medians)
    # Cogemos la mediana o el izquierdo de la mediana en caso de longitud par
    return medians[(medians_len - 1) // 2]


def qsel5_nr(t: np.ndarray, k: int)-> Union[int, None]:
    """Funcion iterativa del algoritmo QuickSelect usando como pivote la mediana de medianas de 5 elementos,
            el cual devuelve el valor de un elemento dada su posicion en una tabla si esta estuviera ordenada
        
        ARGS:
            t (np.ndarray): tabla numerica en la que se buscara el elemento en posicion dada
            k (int): posicion del elemento a encontrar en la tabla ordenada
            
        RETURNS:
            int: valor del elemento en la tabla ordenada o None en caso de no encontrarlo
    """   
    if k < 0 or k >= len(t):
        return None
    
    while True:
        pivot = pivot5(t)
        lower_list, pivot, bigger_list = split_pivot(t, pivot)
    
        pos_pivot = len(lower_list)
        if pos_pivot > k: #comprobamos si el elemento esta en la lista menor
            t = lower_list
        elif pos_pivot == k:
            return pivot
        else:
            t = bigger_list
            k -= pos_pivot + 1


def qsort_5(t: np.ndarray)-> np.ndarray:
    """Funcion que ordena una tabla dada usando como pivote la mediana de medianas de 5 elementos
        
        ARGS:
            t (np.ndarray): tabla a ordenar
            
        RETURNS:
            np.ndarray: ordenancion de la tabla dada
    """
    if len(t) == 0:
        return t

    pivot = pivot5(t)
    lower_list, pivot, bigger_list = split_pivot(t, pivot)
    
    sorted_list = qsort_5(lower_list)
    sorted_list = np.append(sorted_list, [pivot])
    sorted_list = np.append(sorted_list, qsort_5(bigger_list))
    return sorted_list


def edit_distance(str_1: str, str_2: str)-> int:
    """Funcion que calcula el numero minimo de cambios para transformar una cadena en otra
        
        ARGS:
            str_1 (str): Cadena origen
            str_2 (str): Cadena destino
            
        RETURNS:
            int: numero minimo de cambios para transformar la cadena origen en la cadena destino 
    """
    str1_len = len(str_1)
    dist_row = [i for i in range(str1_len + 1)]

    for i in range(1, len(str_2)+1):
        left_value = i
        for j in range(1, str1_len + 1):
            if str_1[j-1] == str_2[i-1]:
                dist_row[j-1], left_value = left_value, dist_row[j-1]
            else:
                min_value = min([left_value] + dist_row[j-1:j+1])
                dist_row[j-1], left_value = left_value, min_value + 1
        dist_row[-1] = left_value

    return dist_row[-1]

def max_subsequence_length(str_1: str, str_2: str)-> int:
    """Longitud de la maxima cadena comun entre dos cadenas dadas
        
        ARGS:
            str_1 (str): Cadena origen
            str_2 (str): Cadena destino

        RETURNS:
            int: longitud de la maxima cadena comun
    """   
    str1_len = len(str_1)
    len_row = [0 for _ in range(str1_len + 1)]
    print(len_row)
    for i in range(1, len(str_2)+1):
        left_value = 0
        for j in range(1, str1_len + 1):
            if str_1[j-1] == str_2[i-1]:
                len_row[j-1], left_value = left_value, len_row[j-1] + 1
            else:
                max_value = max(left_value, len_row[j])
                len_row[j-1], left_value = left_value, max_value
        len_row[-1] = left_value
        print(len_row)

    return len_row[-1]


def max_common_subsequence(str_1: str, str_2: str)-> str:
    """Funcion que busca la maxima cadena comun entre dos cadenas
        
        ARGS:
            str_1 (str): Cadena origen
            str_2 (str): Cadena destino
            
        RETURNS:
            str: maxima cadena comun
    """ 
    if len(str_1) == 0 or len(str_2) == 0:
        return ""
        
    subsequence = ""
    for i in range(len(str_1)):
        new_subsequence = ""
        for j in range(len(str_2)):
            if str_1[i] == str_2[j]:
                b = max_common_subsequence(str_1[i+1:], str_2[j+1:])
                a = str_1[i]
                new_subsequence = a + b
            if len(new_subsequence) > len(subsequence):
                subsequence = new_subsequence

    return subsequence


def getMinMultiplications(l_dims: List[int], i:int, j:int, min_mult_matrix: np.ndarray) -> int:
    """Funcion que devuelve el numero minimo de sub-multiplicaciones para multiplicar varias matrices, dada su lista de dimensiones
        
        ARGS:
            l_dims (List[int]): matriz con las dimensiones de las matices
            i (int): indice de la matriz izquierda
            j (int): indice de la matriz derecha
            min_mult_matrix (np.ndarray): matriz que contiene el minimo numero de multiplicaciones para multiplicar las matrices
            
        RETURNS:
            int: numero minimo de sub-multiplicaciones
    """ 
    min_mults = -1
    left_matrix, right_matrix = i-j+1, i+1 # Le sumamos 1 para que el parentesis se mueva por las matrices intermedias
    for parentesis in range(left_matrix, right_matrix):
        mults = l_dims[left_matrix - 1] * l_dims[parentesis] * l_dims[right_matrix]
        mults += min_mult_matrix[parentesis-1][i-j] + min_mult_matrix[i][parentesis]
        if min_mults == -1 or min_mults > mults:
            min_mults = mults

    return min_mults

def min_mult_matrix(l_dims: List[int])-> int:
    """Funcion que devuelve el minimo numero de multiplicaciones para multiplicar varias matrices dada su lista de dimensiones
        
        ARGS:
            l_dims (List[int]): matriz con las dimensiones de las matrices a multiplicar
            
        RETURNS:
            int: numero minimo de multiplicaciones a realizar para multiplicar las matrices 
    """   
    num_matrices = len(l_dims) - 1

    min_mult_matrix = np.zeros((num_matrices, num_matrices), dtype=int)
    for j in range(1, num_matrices):
        for i in range(j, num_matrices):
            min_mult_matrix[i][i-j] = getMinMultiplications(l_dims, i, j, min_mult_matrix)

    return min_mult_matrix[num_matrices-1][0]
