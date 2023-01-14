import numpy as np
from typing import List, Callable

"""
Autores:
    Daniel Cerrato Sánchez (daniel.cerrato@estudiante.uam.es)
    David T. Garitagoitia Romero (david.garitagoitia@estudiante.uam.es)
"""


def matrix_multiplication(m_1: np.ndarray, m_2: np.ndarray) -> np.ndarray:
    """Metodo que multiplica dos matrices recibidas por argumento
        y devuelve la matriz resultante

        ARGS:
            m_1 (np.ndarray): matriz 1 a multiplicar
            m_2 (np.ndarray): matriz 2 a multiplicar

        RETURNS:
            np.ndarray: Resultado de la multiplicación de las matrices
            """

    # shape = (rows, columns)
    m_1_shape, m_2_shape = m_1.shape, m_2.shape
    if m_1_shape[1] != m_2_shape[0]:
        return None

    m_final = np.zeros(shape=(m_1_shape[0], m_2_shape[1]))
    # Filas de m_1
    for i in range(m_1_shape[0]):
        # Columnas de m_2
        for j in range(m_2_shape[1]):
            # Columnas de m_1 y filas de m_2 a la vez
            for k in range(m_1_shape[1]):
                m_final[i][j] += m_1[i][k] * m_2[k][j]

    return m_final


def rec_bb(t: List, f: int, l: int, key: int) -> int:
    """Metodo que realiza el algoritmo de busqueda binaria recursivamente.
        Devuelve la posicion del elemento buscado en caso de encontrarlo.

        ARGS:
            t (list): lista para hacer la búsqueda
            f (int): índice del primer elemento
            l (int): índice del último elemento de la lista
            key (int): elemento a buscar en la lista

        RETURNS:
            int: índice del elemento a buscar si es que lo encuentra
            """

    if f > l:
        return
    if f == l:
        if key == t[f]:
            return f
        return

    mid = (f + l) // 2
    if t[mid] == key:
        return mid
    if t[mid] < key:
        return rec_bb(t, mid + 1, l, key)
    return rec_bb(t, f, mid - 1, key)


def bb(t: List, f: int, l: int, key: int) -> int:
    """Metodo que realiza el algoritmo de busqueda binaria iterativamente.
        Devuelve la posicion del elemento buscado en caso de encontralo.

        ARGS:
            t (list): lista para hacer la búsqueda
            f (int): índice del primer elemento
            l (int): índice del último elemento de la lista
            key (int): elemento a buscar en la lista

        RETURNS:
            int: índice del elemento a buscar si es que lo encuentra
            """

    while f <= l:
        mid = (f + l) // 2
        if t[mid] == key:
            return mid
        if t[mid] < key:
            f = mid + 1
        else:
            l = mid - 1
    return None


def min_heapify(h: np.ndarray, i: int) -> np.ndarray:
    """Metodo que baja el elemento i-esimo del heap hasta una posicion correcta.
        Devuelve el heap modificado.

        ARGS:
            h (np.ndarray): heap que se desea heapificar
            i (int): índice del elemento que se desea heapificar dentro del heap

        RETURNS:
            np.ndarray: heap resultante del heapify
        """

    h_len = len(h) - 1
    if i < 0 or i > h_len:
        return None

    while 2*i+1 <= h_len:
        n_i = i
        # Compara padre con hijo izquierdo
        if h[i] > h[2*i+1]:
            n_i = 2*i+1
        # Compara padre o hijo izquierdo con hijo derecho
        if 2*i+2 <= h_len and h[i] > h[2*i+2] and h[2*i+2] < h[n_i]:
            n_i = 2*i+2
        # Si algun hijo es menor que el padre, se cambian
        if n_i > i:
            h[i], h[n_i] = h[n_i], h[i]
            i = n_i
        else:
            break

    return h


def insert_min_heap(h: np.ndarray, k: int) -> np.ndarray:
    """Metodo que inserta un elemento k en el heap en una posicion correcta.
        Devuelve el heap modificado
        
        
        ARGS:
            h (np.ndarray): heap en el que se desea insertar
            k (int): elemento que se desea insertar 

        RETURNS:
            np.ndarray: heap tras la inserción"""

    if h is None:
        return np.array([k])

    i = len(h)
    h = np.append(h, k)

    # Mientras el padre sea mayor que el hijo, se cambian
    while i > 0 and h[(i-1)//2] > h[i]:
        h[i], h[(i-1)//2] = h[(i-1)//2], h[i]
        i = (i-1)//2
    return h


def create_min_heap(h: np.ndarray):
    """Metodo que reordena todo el heap de forma correcta.
        Devuelve el heap modificado
        
        
        ARGS:
            h (np.ndarray): colección de elementos para crear el árbol
    """

    if h is None:
        return None

    # Se recorren los nodos internos del heap desde
    # el padre de la ultima hoja hasta la raiz
    for node in range((len(h) - 1) // 2, -1, -1):
        min_heapify(h, node)

    return h


def pq_ini():
    """Metodo que devuelve una cola de prioridad vacia"""

    return np.empty(shape=0)


def pq_insert(h: np.ndarray, k: int) -> np.ndarray:
    """Metodo que inserta un elemento en la cola de prioridad.
        Devuelve la cola modificada
        
        
        ARGS:
            h (np.ndarray): heap en el que se desea insertar
            k (int): elemento que se desea insertar

        RETURNS:
            np.ndarray: Resultado de la inserción en el heap"""

    return insert_min_heap(h, k)


def pq_remove(h: np.ndarray) -> np.ndarray:
    """Metodo que elimina el elemento prioritario de la cola.
        Devuelve el elemento y la cola reordenada
        
        
        ARGS:
            h (np.ndarray): heap en el que se desea eliminar un elemento

        RETURNS:
            np.ndarray: Resultado de la extracción de elementos"""

    if h is None:
        return None, h

    if len(h) <= 0:
        return None, h

    # Búsqueda del elemento menor (por si no está heapificado)
    h_min, pos = h[0], 0
    for i, value in enumerate(h):
        if h_min > value:
            h_min, pos = value, i

    h[pos], h[-1] = h[-1], h[pos]
    return h_min, create_min_heap(h[:-1])


def select_min_heap(h: np.ndarray, k: int) -> int:
    """Metodo que devuelve el k-esimo elemento mayor del heap si existe
    
    
        ARGS:
            h (np.ndarray): colección de elementos del que se desea obtener el k elemento
            k (int): posición del elemento en la lista ordenada que se desea obtener

        RETURNS:
            int: elemento de la k posición"""

    if h is None:
        return None

    if k > len(h) - 1:
      return None

    c = np.negative(h) # convertimos todos los valores del array a negativo
    c = create_min_heap(c)

    for _ in range(k):
      val, c = pq_remove(c)

    if val is None:
        return None
    return -val

def select_min_heap(h: np.ndarray, k: int) -> int:
    """Metodo que devuelve el k-esimo elemento menor del heap si existe empleando max heap
        ARGS:
            h (np.ndarray): colección de elementos del que se desea obtener el k elemento
            k (int): posición del elemento en la lista ordenada que se desea obtener

        RETURNS:
            int: elemento de la k posición"""

    if h is None: #comprobamos que no sea None
        return None

    if k > len(h) - 1: #comprobamos que nos pida una pos válida
      return None

    heap = create_min_heap(np.negative(h[:k+1])) #creas un max heap con esos valores (en la raiz estará el k esimo elemento)
    for i in range(k+1, len(h)):
      val = -h[i]
      if(val>heap[0]):
        heap = heap[1:] #simplemente quitamos la raiz es innecesario el remove dado que inmediatamente después insertamos
        heap = pq_insert(heap, val) #al insertar volvemos a heapificar y se forma el max heap de nuevo

    val = heap[0]
    if val is None:
        return None
    return -val
