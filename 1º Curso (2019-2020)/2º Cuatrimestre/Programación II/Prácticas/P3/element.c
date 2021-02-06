/******************************************************************************
Nombre del modulo: element.c
Descripcion: Implementacion de las funciones de los elementos de la pila
Autor:  
Fecha: 14-03-20
Modulos propios que necesita:
  -element.h
Notas:
Modificaciones:
Mejoras pendientes:
******************************************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "element.h"


/*=== Definiciones ==========================================================*/
struct _Element{
  char *a;
};


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: element_init
Descripcion: Crea un elemento
Argumentos de entrada: Ninguno
Retorno:
- element, un puntero al elemento
- NULL, si falla
-----------------------------------------------------------------------------*/
Element* element_init(){
  Element* element;
  element=(Element*)malloc(sizeof(Element));
  element->a=NULL;
  if(!element){
    return NULL;
  }
  return element;
}

/*-----------------------------------------------------------------------------
Nombre: element_free
Descripcion: Libera un elemento
Argumentos de entrada: Ninguno
Retorno: Nada
-----------------------------------------------------------------------------*/
void element_free(void *element){
  Element *aux;
  aux=element;
  if(!aux){
    return;
  }
  free(aux);
  return;
}

/*-----------------------------------------------------------------------------
Nombre: element_setInfo
Descripcion: Asigna un dato al elemento
Argumentos de entrada:
1. element, el puntero al elemento
2. info, el puntero a la informacion a asignar
Retorno:
- NULL, si falla
- element, el puntero al elemento
-----------------------------------------------------------------------------*/
Element* element_setInfo(Element* element, void* info){
  if(!element || !info){
    return NULL;
  }
  element->a=info;
  return element;
}

/*-----------------------------------------------------------------------------
Nombre: element_getInfo
Descripcion: Obtiene el dato que contiene el elemento
Argumentos de entrada:
1. Element, el puntero al elemento
Retorno:
- NULL, si falla
- a, el puntero al dato que contiene el elemento
-----------------------------------------------------------------------------*/
void* element_getInfo(Element* element){
  if(!element){
    return NULL;
  }
  return element->a;
}

/*-----------------------------------------------------------------------------
Nombre: element_copy
Descripcion: Copia el contenido de un elemento en otro
Argumentos de entrada:
1. element, el puntero al elemento
Retorno:
- NULL, si falla
- aux, el puntero al elemento copiado
-----------------------------------------------------------------------------*/
void* element_copy(const void* element){
  Element *aux=NULL;
  const Element *aux2;
  if(!element){
    return NULL;
  }
  aux=element_init();
  if(!aux){
    return NULL;
  }
  aux2=element;
  aux->a=aux2->a;
  return aux;
}

/*-----------------------------------------------------------------------------
Nombre: element_equals
Descripcion: Compara el contenido de dos elementos
Argumentos de entrada:
1. element, el puntero al primer elemento
2. element2, el puntero al segundo elemento
Retorno:
- FALSE, si falla
- TRUE, si la copia se realiza correctamente
-----------------------------------------------------------------------------*/
Bool element_equals(const Element* element, const Element* element2){
  if(!element || !element2){
    return FALSE;
  }
  if(element->a==element2->a){
    return TRUE;
  }
  return FALSE;
}

/*-----------------------------------------------------------------------------
Nombre: element_print
Descripcion: Imprime un contenido de un elemento
Argumentos de entrada:
1. f, el puntero al fichero
2. element, el puntero al elemento
Retorno:
- -1, si falla
- la impresion del contenido del elemento
-----------------------------------------------------------------------------*/
int element_print(FILE* f, const void* element){
  const Element *aux;
  if(!f || !element){
    return -1;
  }
  aux=element;
  return fprintf(f, "%s ", aux->a);
}
