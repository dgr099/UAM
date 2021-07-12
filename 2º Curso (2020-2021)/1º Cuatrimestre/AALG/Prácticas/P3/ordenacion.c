/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Daniel Cerrato y David Garitagoitia
 * Version: 4.0
 * Fecha: 12-11-2020
 *
 */

#include <stdlib.h>

#include "ordenacion.h"
#include "permutaciones.h"

/*Prototipos de funciones privadas*/

/***************************************************/
/* Funcion: merge         Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena dos tablas en una comparando  */
/* la entrada de una con la de la otra.            */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int imedio: posición intermedia de los números  */
/*             a ordernar                          */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int merge(int *tabla, int ip, int iu, int imedio);

/***************************************************/
/* Funcion: medio         Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ???????????????????????????????????  */
/* ????????????????????????????????????            */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int *pos: ????????????                          */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o 1 en caso  */
/* contrario.                                      */
/***************************************************/
int medio(int *tabla, int ip, int iu, int *pos);

/***************************************************/
/* Funcion: partir        Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ???????????????????????????????????  */
/* ????????????????????????????????????            */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int *pos: ????????????                          */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de opperaciones básicas realizadas.             */
/***************************************************/
int partir(int *tabla, int ip, int iu, int *pos);

/***************************************************/
/* Funcion: InsertSort    Fecha: 26-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena los números mediante          */
/* inserciones empezando por los primeros.         */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* Salida:                                         */
/* int OB: numero de operaciones básicas hechas    */
/***************************************************/
int InsertSort(int *tabla, int ip, int iu)
{
  int i, j, min, OB = 0;

  if (ip > iu)
    return ERR;

  for (i = ip + 1; i <= iu; i++)
  {
    min = tabla[i];
    j = i - 1;
    while (j >= ip && tabla[j] > min)
    {
      OB++;
      tabla[j + 1] = tabla[j];
      j--;
    }
    OB++;
    tabla[j + 1] = min;
  }

  return OB;
}

/***************************************************/
/* Funcion: InsertSortInv Fecha: 26-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena los números mediante          */
/* inserciones empezando por los últimos.          */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* Salida:                                         */
/* int OB: numero de operaciones básicas hechas    */
/***************************************************/
int InsertSortInv(int *tabla, int ip, int iu)
{
  int i, j, max, OB = 0;

  if (ip > iu)
    return ERR;

  for (i = iu - 1; i >= ip; i--)
  {
    max = tabla[i];
    j = i + 1;
    while (j <= iu && tabla[j] < max)
    {
      OB++;
      tabla[j - 1] = tabla[j];
      j++;
    }
    OB++;
    tabla[j - 1] = max;
  }

  return OB;
}

/***************************************************/
/* Funcion: MergeSort     Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena los números dividiendo        */
/* la tabla reiteradas veces a la mitad            */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas recogido de   */
/* la función auxiliar "merge".                    */
/***************************************************/
int MergeSort(int *tabla, int ip, int iu)
{
  int m = 0; /*punto medio*/
  int OBs = 0, aux = 0;
  if (ip > iu)
    return ERR;
  if (ip == iu)
    return 0;
  else
  {
    m = (ip + iu) / 2;
    if ((aux = MergeSort(tabla, ip, m)) == ERR) /*se ordena la primera mitad*/
      return ERR;
    OBs += aux;
    if ((aux = MergeSort(tabla, m + 1, iu)) == ERR) /*se ordena la segunda mitad de la tabla*/
      return ERR;
    OBs += aux;
    if ((aux = merge(tabla, ip, iu, m)) == ERR)
      return ERR;
    OBs += aux;
    return OBs; /*se unen las dos mitades ordenadas de la tabla*/
  }
}

/***************************************************/
/* Funcion: QuickSort     Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena dos tablas en una comparando  */
/* la entrada de una con la de la otra.            */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int imedio: posición intermedia de los números  */
/*             a ordernar                          */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int QuickSort(int *tabla, int p, int u)
{
  int ob = 0, m, aux = 0;
  if (p > u)
    return ERR;
  if (p == u)
    return 0; /*si la tabla tiene solo un elemento ya está ordenada*/
  if ((aux = partir(tabla, p, u, &m)) == ERR)
    return ERR;
  ob += aux; /*poner a la izq los menores y a la derecha los mayores*/
  if (p < m - 1)
  {
    if ((aux = QuickSort(tabla, p, m - 1)) == ERR)
      return ERR;
    ob += aux; /*ordenas la tabla formada por los menores del pivote*/
  }
  if (m + 1 < u)
  {
    if ((aux = QuickSort(tabla, m + 1, u)) == ERR)
      ob += aux; /*ordenas la tabla formada por los mayores del pivote*/
  }
  return ob;
}

/***************************************************/
/* Funcion: QuickSort     Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena dos tablas en una comparando  */
/* la entrada de una con la de la otra             */
/* (sin la recursión.)                             */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int imedio: posición intermedia de los números  */
/*             a ordernar                          */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int QuickSort_src(int *tabla, int p, int u)
{
  int ob = 0, m, aux;
  while (p != u)
  {
    if (p > u)
      return ERR;
    if ((aux = partir(tabla, p, u, &m)) == ERR) /*poner a la izq los menores y a la derecha los mayores*/
      return ERR;
    ob += aux;
    p = m + 1;
  }
  return ob;
}

/* Funciones privadas */
/***************************************************/
/* Funcion: Merge         Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que combina dos tablas ordenadas en una  */
/* nueva tabla ordenada que contiene los elementos */
/* de ambas tablas                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número de           */
/* la tabla 1                                      */
/* int iu: posición del último número de           */
/* la tabla 2                                      */
/* int imedio: posición del ultimo elemento de     */
/* la tabla 1 y anterior al primer elemento de     */
/* la tabla 2                                      */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int merge(int *tabla, int ip, int iu, int imedio)
{
  int *t_aux = NULL;
  int OB = 0;                                 /*operación básica*/
  int i_aux = ip, j_aux = imedio + 1, it = 0; /*tres indices que corresponden dos a las tablas a ordenar y un tercero a la tabla total*/
  if ((t_aux = (int *)malloc(iu - ip + 1 * sizeof(int))) == NULL)
    return ERR; /*tabla auxiliar de tamaño el de la tabla a ordenar*/
  while (i_aux <= imedio && j_aux <= iu)
  { /*mientras no se termine de ordenar alguna de las tablas*/
    if (tabla[i_aux] < tabla[j_aux])
    { /*si el valor de la tabla de la 1º mitad es menor*/
      t_aux[it] = tabla[i_aux];
      /*actualizas el índice de la tabla afectada*/
      i_aux++;
    }
    else
    {
      t_aux[it] = tabla[j_aux];
      j_aux++;
    }
    OB++;
    it++;
  }
  /*al llegar aqui una tabla estará aun por ordenar*/
  while (i_aux <= imedio)
  { /*mientras la tabla izq no esté completamente vacía*/
    OB++;
    t_aux[it] = tabla[i_aux];
    i_aux++;
    it++;
  }
  while (j_aux <= iu)
  { /*mientras la tabla der no esté completamente vacía*/
    OB++;
    t_aux[it] = tabla[j_aux];
    j_aux++;
    it++;
  }
  OB++; /*la comparción de índices no exitosa*/
  /*Al llegar a este punto la tabla t_aux está completamente ordenada*/
  /*colocamos la sub tabla ordenada entre los indices en la tabla total*/
  it = 0;
  for (; ip <= iu; ip++, it++)
  {
    tabla[ip] = t_aux[it];
  }
  free(t_aux);
  return OB; /*retornas la operación básica*/
}

/***************************************************/
/* Funcion: Medio         Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que guarda en pos el valor de la         */
/* posición del número que utilizaremos            */
/* como pivote                                     */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int pos: puntero donde guardaremos el valor de  */
/*          la posicion del número a usar          */
/*          como pivote                            */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int medio(int *tabla, int ip, int iu, int *pos)
{ /*utilizaremos como pivote el elemento de la primera posición*/
  if (!tabla || ip > iu)
    return ERR;
  (*pos) = ip;
  return OK;
}

/***************************************************/
/* Funcion: partir        Fecha: 30-10-2020        */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que ordena el pivote y deja a            */
/* la izquiera todos los elementos menores a el    */
/* y a la derecha todos los elementos mayores a el */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de números                    */
/* int ip: posición del primer número a ordenar    */
/* int iu: posición del último número a ordenar    */
/* int pos: posición del elemento pivote           */
/*                                                 */
/* Salida:                                         */
/* Puede ser ERR, si algo ha ido mal, o el número  */
/* de operaciones básicas realizadas.              */
/***************************************************/
int partir(int *tabla, int ip, int iu, int *pos)
{
  int ob = 0, k, obs, i;
  if ((obs = medio(tabla, ip, iu, pos)) == ERR)
    return ERR;
  ob += obs;
  k = tabla[*pos]; /*k toma el valor del pivote*/
  for (i = ip; i <= iu; i++)
  {
    if (tabla[i] < k)
    {
      ob++; /*cuenta comparaciones exitosas*/
      (*pos)++;
      swap(&tabla[i], &tabla[*pos]);
    }
  }
  ob++; /*para compensar la comparacion no exitosa*/
  swap(&tabla[ip], &tabla[*pos]);
  return ob;
}
