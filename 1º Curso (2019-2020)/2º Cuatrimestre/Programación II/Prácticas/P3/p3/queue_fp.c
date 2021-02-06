/**************************************************
Nombre del modulo: queue_fp.c
Descripcion: Funciones necesarias para trabajar con colas
Autor:  
Fecha: 18-03-20
Modulos propios que necesita: queue_fp.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_fp.h"


/*=== Definiciones ==========================================================*/

#define MAXQUEUE 1024

struct _Queue {
  void* items [MAXQUEUE];
  int front;
  int rear;
  free_element_function_type free_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: queue_init
Descripcion: inicializa una cola
Argumentos de entrada:
1. fd, puntero a funcion para liberar un elemento de la cola
2. fc, puntero a funcion para copiar un elemento de la cola
3. fp, puntero a funcion para imprimir un elemento de la cola
Retorno:
- q, el puntero a la cola
- NULL, en caso de error
-----------------------------------------------------------------------------*/
Queue *queue_init(free_element_function_type fd, copy_element_function_type fc, print_element_function_type fp){
  Queue *q=NULL;
  int i;
  if(!fd || !fc || !fp){
    return NULL;
  }
  if(!(q=(Queue*)calloc(1, sizeof(Queue)))){
    return NULL;
  }
  q->copy_element_function = fc;
  q->free_element_function = fd;
  q->print_element_function = fp;
  for(i=0; i!=MAXQUEUE; i++){
    q->items[i] = NULL;
  }
  q->front=q->rear=0;
  return q;
}

/*-----------------------------------------------------------------------------
Nombre: queue_free
Descripcion: libera la memoria usada por la cola
Argumentos de entrada:
1. q, el puntero a la cola
Retorno: nada
-----------------------------------------------------------------------------*/
void queue_free(Queue *q){
  int i;
  if(!q){
    return;
  }
  i=q->front;
  for(; q->items[i]!=NULL; i=(i+1)%MAXQUEUE){
    q->free_element_function(q->items[i]);
  }
  free(q);
}

/*-----------------------------------------------------------------------------
Nombre: queue_isEmpty
Descripcion: determina si la cola esta vacia
Argumentos de entrada:
1. q, el puntero a la cola
Retorno:
- TRUE, si esta vacia
- FALSE, si no esta vacia
-----------------------------------------------------------------------------*/
Bool queue_isEmpty(const Queue *q){
  if(!q){
    return TRUE;
  }
  if(q->rear==q->front){
    return TRUE;
  }
  return FALSE;
}

/*-----------------------------------------------------------------------------
Nombre: queue_insert
Descripcion: inserta un elemento en la cola
Argumentos de entrada:
1. q, el puntero a la cola
2. pElem, el puntero al elemento a insertar
Retorno:
- OK, si funciona correctamente
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status queue_insert(Queue *q, const void* pElem){
  void* aux;
  if(!q || !pElem){
    return ERROR;
  }
  if(queue_size(q)>=MAXQUEUE-1){
    return ERROR;
  }
  aux=q->copy_element_function(pElem);
  q->items[q->rear]=aux;
  q->rear=(q->rear+1)%MAXQUEUE;
  return OK;
}

/*-----------------------------------------------------------------------------
Nombre: queue_extract
Descripcion: extrae un elemento de la cola
Argumentos de entrada:
1. q, el puntero a la cola
Retorno:
- NULL, en caso de error
- aux, el puntero al elemento extraido
-----------------------------------------------------------------------------*/
void * queue_extract(Queue *q){
  void* aux;
  if(!q || queue_isEmpty(q)==TRUE){
    return NULL;
  }
  aux=q->items[q->front];
  q->items[q->front]=NULL;
  q->front=(q->front+1)%MAXQUEUE;
  return aux;
}

/*-----------------------------------------------------------------------------
Nombre: queue_size
Descripcion: devuelve el tamaño de la cola
Argumentos de entrada:
1. q, el puntero a la cola
Retorno:
- -1, en caso de error
- i, el tamaño de la cola
-----------------------------------------------------------------------------*/
int queue_size (const Queue *q){
  int aux1, aux2, i;
  if(!q){
    return -1;
  }
  aux1=q->front;
  aux2=q->rear;
  for(i=0; aux1!=aux2; i++){
    aux1=(aux1+1)%MAXQUEUE;
  }
  return i;
}

/*-----------------------------------------------------------------------------
Nombre: queue_print
Descripcion: imprime los elementos de la cola
Argumentos de entrada:
1. pf, el puntero al fichero en el que escribir
2. q, el puntero a la cola
Retorno:
- -1, en caso de error
- cont, el numero de caracteres escritos
-----------------------------------------------------------------------------*/
int queue_print(FILE *pf, const Queue *q){
  int i, cont, z, h;
  if( !pf || !q ){
    return -1;
  }
  z=queue_size(q);
  for(i=cont=h=0; i!=z; i++, h++){
    if(q->items[h]!=NULL){
      cont=q->print_element_function(pf, q->items[h]);
    }
    else
      i--;
  }
  return cont;
}
