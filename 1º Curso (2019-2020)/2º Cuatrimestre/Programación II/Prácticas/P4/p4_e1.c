/**************************************************
Nombre del modulo: p4_e1.c
Descripcion: Impresion de dos listas concatenadas
Autor:  
Fecha: 19-04-20
Modulos propios que necesita: types.h list.h stack_types.h stack_fp.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "list.h"
#include "stack_types.h"
#include "stack_fp.h"


/*=== Definiciones ==========================================================*/
#define MAX_ID 1000

/* Type definition. Pointer function to compare two elements */
typedef int (*f_cmp_type)(const void* ele1, const void* ele2);


/*=== Funciones =============================================================*/
/*-----------------------------------------------------------------------------
Nombre: int_print_v2
Descripcion: imprime elementos con espacios entre ellos
Argumentos de entrada:
1. pf, el dispositivo en el que se desea imprimir los valores
2. ele, puntero al elemento a imprimir
Retorno:
- -1, en caso de error
- numero de caracteres impreso
-----------------------------------------------------------------------------*/
int int_print_v2(FILE *pf, const void *ele){
  if(!ele || !pf){
    return -1;
  }
  return fprintf(pf, "%d ", *(int*)ele);
}

/*-----------------------------------------------------------------------------
Nombre: listOfRandomOrdered
Descripcion: inserta n enteros aleatorios entre 0 y MAX_ID en una lista ordenada
Argumentos de entrada:
1. n, la longitud de la lista
2. pl, puntero a la lista
Retorno:
- OK, si funciona correctamente
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status listOfRandomOrdered (int n, List *pl){
    int i=0, *alt;
    Status st=OK;

    if (!pl) 
        return ERROR;

    for (i=0; i!=n && st == OK; i++) {
        alt=(int*)malloc(sizeof(int));
        (*alt) = rand ()%MAX_ID;
        st = list_pushOrder (pl, alt, 1);
        int_free(alt);
    }

    if (st == ERROR) {
        return ERROR;
    }

    return OK;
}

/*-----------------------------------------------------------------------------
Nombre: listMergeOrdered
Descripcion: concatena dos listas en orden ascendente
Argumentos de entrada:
1. l1, puntero a la primera lista
2. l2, puntero a la segunda lista
Retorno:
- OK, si funciona correctamente
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status listMergeOrdered (List *li, List *l2, List *lout, f_cmp_type fun){
  int* integer;  
  Status st=OK;
  Stack *aux1, *aux2, *paux;
  List *laux;;

  if(!li || !l2 || !lout || !fun)
    return ERROR;
  if(!(aux1=stack_init(int_free, int_copy, int_print)))
    return ERROR;
  if(!(aux2=stack_init(int_free, int_copy, int_print)))
    stack_free(aux1);
  while(list_isEmpty(li)!=TRUE && st==OK){
    integer=list_popFront(li);
    st=stack_push(aux1, integer);
    int_free(integer);
  }
  while(list_isEmpty(l2)!=TRUE && st==OK){
    integer=list_popFront(l2);
    st=stack_push(aux2, integer);
    int_free(integer);
  }
  while(stack_isEmpty(aux1)==FALSE && stack_isEmpty(aux2)==FALSE){
    if(fun(stack_top(aux1), stack_top(aux2))>0){
      integer=stack_pop(aux1);
      list_pushFront(li, integer);
      list_pushFront(lout, integer);
      int_free(integer);
    }
    else{
      integer=stack_pop(aux2);
      list_pushFront(l2, integer);
      list_pushFront(lout, integer);
      int_free (integer); 
    }
  }
  if(stack_isEmpty(aux1)!=TRUE){
    paux=aux1;
    laux=li;
  }
  else
  {
    paux=aux2;
    laux=l2;
  }
  while(stack_isEmpty(paux)!=TRUE){
    integer=stack_pop(paux);
    list_pushFront(laux, integer);
    list_pushFront(lout, integer);
    int_free(integer);
  }
  stack_free(aux1);
  stack_free(aux2);
  return st;
}

/******************************************************************************/

int main (int argc, char **argv){
  List *lista1, *lista2, *lista3;
  if(argc<2){
    return 1;
  }
  if(!(lista1=list_new(int_free, int_copy, int_print_v2, int_cmp))){
    return 1;
  }
  if(!(lista2=list_new(int_free, int_copy, int_print_v2, int_cmp))){
    list_free(lista1);
    return 1;
  }
  if(!(lista3=list_new(int_free, int_copy, int_print_v2, int_cmp))){
    list_free(lista1);
    list_free(lista2);
    return 1;
  }
  /**integer=383;
  list_pushBack(lista1, integer);
  *integer=777;
  list_pushBack(lista1, integer);
  *integer=793;
  list_pushBack(lista1, integer);
  *integer=886;
  list_pushBack(lista1, integer);
  *integer=915;
  list_pushBack(lista1, integer);
  *integer=335;
  list_pushBack(lista2, integer);
  *integer=386;
  list_pushBack(lista2, integer);
  *integer=421;
  list_pushBack(lista2, integer);
  *integer=492;
  list_pushBack(lista2, integer);
  *integer=649;
  list_pushBack(lista2, integer);*/
  srand (time(NULL));
  listOfRandomOrdered(atol(argv[1]), lista1);
  listOfRandomOrdered(atol(argv[1]), lista2);
  fprintf(stdout, "List 0:\n");
  list_print(stdout, lista1);
  fprintf(stdout, "size: %d\n", list_size(lista1));
  fprintf(stdout, "List 1:\n");
  list_print(stdout, lista2);
  fprintf(stdout, "size: %d\n", list_size(lista2));
  listMergeOrdered(lista1, lista2, lista3, int_cmp);
  fprintf(stdout, "List 2:\n");
  list_print(stdout, lista3);
  fprintf(stdout, "size: %d\n", list_size(lista3));
  list_free(lista1);
  list_free(lista2);
  list_free(lista3);
  return 0;
}
