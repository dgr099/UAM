/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 2.0
 * Fecha: 26-10-2020
 *
 */
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"

void libera_memoria(int *claves, PDICC dic)
{
  free(claves);
  libera_diccionario(dic);
  return;
}

/******************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha: 26-10-2020 */
/* Autores: Daniel Cerrato y David Garitagoitia       */
/*                                                    */
/* Rutina que calcula el tiempo medio de ordenación   */
/* del método obtenido, además de las OBs medias,     */
/* mínimas y máximas.                                 */
/*                                                    */
/* Entrada:                                           */
/* pfunc_ordena metodo: metodo de ordenacion          */
/* int n_perms: numero de permutaciones a crear       */
/* int N: tamaño de las permutaciones                 */
/* PTIEMPO ptiempo: puntero a estructura TIEMPO       */
/* Salida:                                            */
/* OK en el caso de que todo haya ido correctamente,  */
/* ERR en el caso opuesto.                            */
/******************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int N, PTIEMPO ptiempo)
{
  clock_t ini, end;
  int i, ob, obs = 0, ob_min = INT_MAX, ob_max = 0;
  /*generamos las n permutaciones de tamaño N*/
  int **perms = (int **)genera_permutaciones(n_perms, N);
  /*Si se produce un error en la generación de permutaciones devolvemos error*/
  if (perms == NULL)
    return ERR;
  /*tiempo de inicio de la ejecución*/
  ini = clock();
  /*mientrás no se produzcan errores y queden permutaciones por ordenar*/
  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(perms[i], 0, N - 1); /*se ordena la permutación y se obtienen las operaciones basicas de dicha ordenación*/
    if (ob == ERR)
    { /*si ocurre un error en la ordenacion se libera la memoria y se retorna error*/
      for (i = 0; i < n_perms; i++)
        free(perms[i]);
      free(perms);
      return ERR;
    }
    obs += ob;       /*se suman las operaciones básicas al total*/
    if (ob < ob_min) /*se actualizan los valores de los máximos y mínimos*/
      ob_min = ob;
    else if (ob > ob_max)
      ob_max = ob;
  }

  end = clock(); /*se guarda el tiempo de finalización*/

  ptiempo->N = N;             /*se guarda el tamaño de cada permutación*/
  ptiempo->n_elems = n_perms; /*se guarda el numero de permutaciones*/
  ptiempo->tiempo = (double)(end - ini) / n_perms / CLOCKS_PER_SEC /*tiempo de ejecución medio*/;
  ptiempo->medio_ob = (double)obs / n_perms; /*la media de operaciones basicas*/
  ptiempo->min_ob = ob_min;                  /*el mínimo de operaciones básicas*/
  ptiempo->max_ob = ob_max;                  /*el máximo de operaciones báscias*/

  for (i = 0; i < n_perms; i++)
    free(perms[i]);
  free(perms);

  return OK;
}

/*********************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha: 26-10-2020  */
/* Autores: Daniel Cerrato y David Garitagoitia          */
/*                                                       */
/* Rutina que genera llamadas a la funcion de cálculo    */
/* tiempos medios de ordenación y a la función que       */
/* guarda los datos en un archivo.                       */
/*                                                       */
/* Entrada:                                              */
/* pfunc_ordena metodo: metodo de ordenacion             */
/* char *fichero: string con el nombre del archivo       */
/*                donde se van a guardar los datos       */
/* int num_min: tamaño minimo de permutaciones           */
/* int num_max: tamaño maximo de permutaciones           */
/* int incr: incremento para llegar de num_min a num_max */
/* int n_perms: numero de permutaciones a generar        */
/* Salida:                                               */
/* OK en el caso de que todo haya ido correctamente,     */
/* ERR en el caso opuesto.                               */
/*********************************************************/

short genera_tiempos_ordenacion(pfunc_ordena metodo, char *fichero, int num_min, int num_max, int incr, int n_perms)
{
  PTIEMPO t = NULL;
  int i = 0, n_tiempos, tamanio = num_min;

  if (num_min > num_max)
    return ERR;

  n_tiempos = (num_max - num_min) / incr + 1;

  if ((t = (PTIEMPO)malloc(n_tiempos * sizeof(t[0]))) == NULL)
    return ERR;

  for (i = 0; i != n_tiempos; i++)
  { /*como cada permutacion es de un tamaño distinto*/
    if (tiempo_medio_ordenacion(metodo, n_perms, tamanio, &t[i]) == ERR)
    { /*si da error la ejecución del programa, salimos del bucle para liberar memoria*/
      free(t);
      return ERR;
    }
    tamanio += incr; /*vamos incrementando el tamaño de las permutaciones*/
  }

  guarda_tabla_tiempos(fichero, t, n_tiempos);

  /*finalmente, tras ejecutar toda la funcion sin errores, liberamos la memoria*/
  free(t);
  return OK;
}

/*********************************************************/
/* Funcion: guarda_tabla_tiempos      Fecha: 26-10-2020  */
/* Autores: Daniel Cerrato y David Garitagoitia          */
/*                                                       */
/* Rutina que guarda los datos almacenados en un fichero */
/*                                                       */
/* Entrada:                                              */
/* char *fichero: string con el nombre del archivo       */
/*                donde se van a guardar los datos       */
/* PTIEMPO ptiempo: puntero a estructura TIEMPO          */
/* int n_tiempos: número de incrementos que hay que      */
/*                hacer para llegar de num_min a num_max */
/* Salida:                                               */
/* OK en el caso de que todo haya ido correctamente,     */
/* ERR en el caso opuesto.                               */
/*********************************************************/
short guarda_tabla_tiempos(char *fichero, PTIEMPO tiempo, int n_tiempos)
{
  int i;
  FILE *f;

  if ((f = fopen(fichero, "w")) == NULL)
    return ERR;

  for (i = 0; i != n_tiempos; i++)
  {
    /*se van imprimiendo los valores*/
    fprintf(f, "%i %.10f %f %i %i\n", tiempo[i].N, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].max_ob, tiempo[i].min_ob);
  }

  fclose(f);

  return OK;
}

/**********************************************************/
/* Funcion: tiempo_medio_busqueda   Fecha: 23-11-2020     */
/* Autores: Daniel Cerrato y David Garitagoitia           */
/*                                                        */
/* Rutina que calcula el tiempo medio de búsqueda         */
/* del método obtenido, además de las OBs medias,         */
/* mínimas y máximas.                                     */
/*                                                        */
/* Entrada:                                               */
/* pfunc_busqueda metodo: metodo de busqueda              */
/* pfunc_generador_claves generador: generador de claves  */
/* int orden: entero que define si la tabla está ordenada */
/* int n_veces: numero de veces que se buscan las claves  */
/* int N: tamaño del diccionario                          */
/* PTIEMPO ptiempo: puntero a estructura TIEMPO           */
/* Salida:                                                */
/* OK en el caso de que todo haya ido correctamente,      */
/* ERR en el caso opuesto.                                */
/**********************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, int n_veces, int N, PTIEMPO ptiempo)
{
  PDICC dic = NULL;
  int *claves = NULL, ppos;
  int aux = n_veces * N; /*utilizamos el aux para no repetir constantemente la multiplicación*/
  clock_t ini, end;
  long int i, ob, obs = 0, ob_min = INT_MAX, ob_max = 0;

  if (!(dic = ini_diccionario(N, orden)))
    return ERR;

  /*generamos una permutación de tamaño N para insertar en el diccionario */
  if ((claves = genera_perm(N)) == NULL)
  {
    libera_memoria(claves, dic);
    return ERR;
  }
  /*Insertamos la permutación de forma masiva en el diccionario */
  insercion_masiva_diccionario(dic, claves, N);

  free(claves);

  /*Reserva de memoria para la tabla que contendrá N*n_veces claves */
  claves = (int *)malloc(aux * sizeof(int));
  if (claves == NULL)
  {
    libera_memoria(claves, dic);
    return ERR;
  }

  /* Creamos una lista de N*n_veces claves a buscar */
  generador(claves, aux, N);
  if (claves == NULL)
  {
    libera_memoria(claves, dic);
    return ERR;
  }

  /*tiempo de inicio de la ejecución*/
  ini = clock();

  for (i = 0; i < aux; i++)
  {
    ob = busca_diccionario(dic, claves[i], &ppos, metodo); /*se busca la clave i-esima y se obtienen las operaciones basicas de dicha busqueda*/
    /*--->duda*/
    if (ob == ERR)
    /*--->duda*/
    { /*si ocurre un error en la ordenacion se libera la memoria y se retorna error*/
      libera_memoria(claves, dic);
      return ERR;
    }
    obs += ob;       /*se suman las operaciones básicas al total*/
    if (ob < ob_min) /*se actualizan los valores de los máximos y mínimos*/
      ob_min = ob;
    else if (ob > ob_max)
      ob_max = ob;
  }
  end = clock(); /*se guarda el tiempo de finalización*/

  ptiempo->N = N;         /*se guarda el tamaño de la biblioteca*/
  ptiempo->n_elems = aux; /*se guarda el numero de claves buscadas */
  ptiempo->tiempo = (double)(end - ini) / aux / CLOCKS_PER_SEC /*tiempo de ejecución medio*/;
  ptiempo->medio_ob = (double)obs / aux; /*la media de operaciones basicas*/
  ptiempo->min_ob = ob_min;                             /*el mínimo de operaciones básicas*/
  ptiempo->max_ob = ob_max;                             /*el máximo de operaciones báscias*/
  libera_memoria(claves, dic);
  return OK;
}

/**********************************************************/
/* Funcion: genera_tiempos_busqueda   Fecha: 23-11-2020   */
/* Autores: Daniel Cerrato y David Garitagoitia           */
/*                                                        */
/* Rutina que genera llamadas a la funcion de cálculo     */
/* tiempos medios de busqueda y a la función que          */
/* guarda los datos en un archivo.                        */
/*                                                        */
/* Entrada:                                               */
/* pfunc_ordena metodo: metodo de busqueda                */
/* pfunc_generador_claves generador: generador de claves  */
/* char *fichero: string con el nombre del archivo        */
/*                donde se van a guardar los datos        */
/* int orden: entero que define si la tabla esta ordenada */
/* int num_min: tamaño minimo de permutaciones            */
/* int num_max: tamaño maximo de permutaciones            */
/* int incr: incremento para llegar de num_min a num_max  */
/* int n_veces: numero de veces que se busca las claves   */
/* Salida:                                                */
/* OK en el caso de que todo haya ido correctamente,      */
/* ERR en el caso opuesto.                                */
/**********************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, char *fichero, int num_min, int num_max, int incr, int n_veces)
{
  PTIEMPO t = NULL;
  int i = 0, n_tiempos, tamanio = num_min;

  if (num_min > num_max)
    return ERR;

  n_tiempos = (num_max - num_min) / incr + 1;

  if ((t = (PTIEMPO)malloc(n_tiempos * sizeof(t[0]))) == NULL)
    return ERR;

  for (i = 0; i != n_tiempos; i++)
  { /*como cada permutacion es de un tamaño distinto*/
    if (tiempo_medio_busqueda(metodo, generador, orden, n_veces, tamanio, &t[i]) == ERR)
    { /*si da error la ejecución del programa, salimos del bucle para liberar memoria*/
      free(t);
      return ERR;
    }
    tamanio += incr; /*vamos incrementando el tamaño de las permutaciones*/
  }

  guarda_tabla_tiempos(fichero, t, n_tiempos);

  /*finalmente, tras ejecutar toda la funcion sin errores, liberamos la memoria*/
  free(t);
  return OK;
}