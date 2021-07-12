/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Daniel Cerrato y David Garitagoitia
 * Version: 4.0
 * Fecha: 26-10-2020
 *
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>
unsigned long idum=3;
#include "permutaciones.h"

/***************************************************/
/* Funcion: swap      Fecha: 26-10-2020            */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que intercambia dos valores              */
/*                                                 */
/* Entrada:                                        */
/* int *a: valor 1                                 */
/* int *b: valor 2                                 */
/***************************************************/
void swap(int *a, int *b){
  int aux = *a;

  *a = *b;
  *b = aux;
}


/***************************************************/
/* Funcion: aleat_num Fecha: 26-10-2020            */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int aleat: numero aleatorio                     */
/***************************************************/

void idum_act(){
  idum=time(NULL);
}

int aleat_num(int inf, int sup)
{
  /*generador uniforme*/
  long a=(long)pow(7, 5); /*multiplicador que de la serie completa*/
  long m=(long)pow(2, 31)-1; /*Mayor primo posible con 32 bits*/
  /*I(j+1)= mod(m)(A * I(j) + C)*/
  /*m es el modulo, a el multiplicador y c el incremento*/
  idum=(a*idum)%m; /*con esto obtenemos el siguiente número de la serie*/
  /*superior - inferior + 1 nos da el numero de numeros que puede tomar
  por ejemplo de 3 a 5 puede tomar el 3, 4, 5 que son 3 numeros = 5-3+1=3*/
  /*al multiplicarlo por idum/m genera números entre 0 y (sup-inf)*/
  /*finalmente sumando el inf obtenemos los numeros en el ranfo deseado*/
  return (inf + ((sup - inf + 1)*idum)/m);
}


/***************************************************/
/* Funcion: genera_perm Fecha: 26-10-2020          */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Rutina que genera una permutación               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int* perm: puntero a un array de enteros        */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N)
{
  int i;
  int *perm = (int *)malloc(N*sizeof(perm[0]));

  if (perm == NULL)
    return NULL;

  for (i = 0; i < N; i++)
    perm[i] = i+1;
 
  for (i = 0; i < N; i++){
    /*se hacen swaps en posiciones aleatorias*/
    swap(&perm[i], &perm[aleat_num(i,N-1)]);
  }
    
  return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 26-10-2020 */
/* Autores: Daniel Cerrato y David Garitagoitia    */
/*                                                 */
/* Función que genera "n_perms" permutaciones      */
/* aleatorias de "tamanio" elementos               */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int** permutas: Array de punteros a enteros     */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  int **permutas = (int **)malloc(n_perms * sizeof(permutas[0]));
  int i;
  
  for (i = 0; i < n_perms; i++){
    permutas[i] = genera_perm(N);
    if (permutas[i] == NULL){
      for (i = 0; i < n_perms; i++)
        free(permutas[i]);
      free(permutas);
    }
  }

  return permutas;
}

