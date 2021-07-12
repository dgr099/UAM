/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"
#include "permutaciones.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for (i = 0; i < n_claves; i++)
    claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for (i = 0; i < n_claves; i++)
  {
    claves[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

PDICC ini_diccionario(int tamanio, char orden)
{
  PDICC dic = NULL;
  dic = (PDICC)malloc(1 * sizeof(DICC));
  if (!(dic->tabla = (int *)malloc(tamanio * sizeof(int))))
    return NULL;

  dic->orden = orden;
  dic->tamanio = tamanio;
  dic->n_datos = 0;

  return dic;
}

void libera_diccionario(PDICC pdicc)
{
  free(pdicc->tabla);
  free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave)
{
  int aux;
  if (!pdicc)
    return 0;

  switch (pdicc->orden)
  {
  case ORDENADO:
    if (pdicc->n_datos == pdicc->tamanio)
    {
      return ERR;
    }
    aux = pdicc->n_datos;
    while (aux != 0 && pdicc->tabla[aux - 1] > clave)
    {
      pdicc->tabla[aux] = pdicc->tabla[aux - 1];
      aux--;
    }
    pdicc->tabla[aux] = clave;
    pdicc->n_datos++;
    return pdicc->n_datos - aux; /*los elementos entre ultimo y la posicion*/
    break;

  default:
    if (pdicc->n_datos == pdicc->tamanio)
    {
      return ERR;
    }
    pdicc->tabla[(pdicc->n_datos)++] = clave;
    /*pdicc->n_datos++;*/
    return 1;
    break;
  }
}

int insercion_masiva_diccionario(PDICC pdicc, int *claves, int n_claves)
{
  int i, ob, OBs = 0;

  for (i = 0; i < n_claves; i++)
  {
    if ((ob = inserta_diccionario(pdicc, claves[i])) == ERR)
      return ob;
    OBs += ob;
  }

  return OBs;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
  if (!pdicc || !ppos || !metodo)
    return ERR;

  return metodo(pdicc->tabla, 0, pdicc->n_datos, clave, ppos);
}

/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U, int clave, int *ppos)
{
  int m = (P + U) / 2;
  int aux = 0;
  /*esto se considera ob?*/
  if (P > U)
  {
    (*ppos) = NO_ENCONTRADO;
    return ERR;
  }
  if (tabla[m] == clave)
  {
    (*ppos) = m;
    return 2;
  }
  if (tabla[m] > clave)
  { /*si esta por la parte izquierda*/
    if ((aux = bbin(tabla, P, --m, clave, ppos)) == ERR)
      return ERR;
    return (3 + aux);
  }
  /*si esta por la parte derecha*/
  if ((aux = bbin(tabla, ++m, U, clave, ppos)) == ERR)
    return ERR;
  return (3 + aux);
}

int blin(int *tabla, int P, int U, int clave, int *ppos)
{
  if (!tabla || !ppos || P < 0)
  {
    return ERR;
  }
  for ((*ppos) = P; (*ppos) != U; (*ppos)++)
  {
    if (tabla[(*ppos)] == clave)
    {
      return (*ppos) - P + 1; /*tantas comparaciones de clave como elementos entre el primero y la posición donde lo encontraste*/
    }
  }
  (*ppos) = NO_ENCONTRADO;
  return (ERR); /*tantas comparaciones de clave como tamaño de la tabla*/
}

int blin_auto(int *tabla, int P, int U, int clave, int *ppos)
{
  int aux = 0;
  aux = blin(tabla, P, U, clave, ppos);
  /*es una búsqueda lineal que avanza una posición la clave para que la próxima vez que los busques tengas que hacer menos cdcs*/
  /*la idea es que se ordenen según la frecuencia de consulta*/
  if (*ppos != NO_ENCONTRADO && *ppos != 0)
    swap(&tabla[(*ppos)], &tabla[(*ppos) - 1]);
  return aux;
}
