/**************************************************
Nombre del modulo: stack.c
Descripcion: Funciones relacionadas con el manejo de pilas
Autor:  
Fecha: 14-03-20
Modulos propios que necesita:
- stack.h
- element.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "element.h"


/*=== Definiciones ==========================================================*/
#define MAXSTACK 1024
struct _Stack {
  int top;
  Element * item[MAXSTACK];
};


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: stack_init
Descripcion: Inicializa una pila vacia
Argumentos de entrada: ninguno
Retorno:
- NULL, si falla
- stack, el puntero a la pila creado
-----------------------------------------------------------------------------*/
Stack* stack_init (){
  Stack *stack;
  if((stack=(Stack*)calloc(1, sizeof(Stack)))==NULL){
    return NULL;
  }
  stack->top=-1;
  return stack;
}

/*-----------------------------------------------------------------------------
Nombre: stack_free
Descripcion: Libera la memoria usada por una pila
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno: nada
-----------------------------------------------------------------------------*/
void stack_free(Stack *stack){
  int i;
  if(!stack){
    return;
  }
  for(i=0; i<=stack->top; i++){
    element_free(stack->item[i]);
    stack->item[i]=NULL;
  }
  free(stack);
  return;
}

/*-----------------------------------------------------------------------------
Nombre: stack_push
Descripcion: Inserta un elemento en el tope de la pila
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- ERROR, si falla
- OK, si termina correctamente
-----------------------------------------------------------------------------*/
Status stack_push(Stack *stack, const Element *element){
  Element *aux;
  if((aux=element_copy(element))==NULL || !stack || !element){
    return ERROR;
  }
  if(stack_isFull(stack)==TRUE){
    return ERROR;
  }
  stack->top++;
  stack->item[stack->top]=aux;
  return OK;
}

/*-----------------------------------------------------------------------------
Nombre: stack_pop
Descripcion: Extrae un elemento del tope de la pila
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- NULL, si falla
- aux, el puntero al elemento extraido
-----------------------------------------------------------------------------*/
Element* stack_pop(Stack *stack){
  Element *aux;
  if(!stack || stack_isEmpty(stack)==TRUE){
    return NULL;
  }
  aux=stack->item[stack->top];
  stack->item[stack->top]=NULL;
  stack->top--;
  return aux;
}

/*-----------------------------------------------------------------------------
Nombre: stack_top
Descripcion: Referencia al elemento que esta en el tope de la pila
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- NULL, si falla
- top, el puntero al elemento que esta en el tope
-----------------------------------------------------------------------------*/
Element* stack_top(const Stack *stack){
  if(!stack){
    return NULL;
  }
  return stack->item[stack->top];
}

/*-----------------------------------------------------------------------------
Nombre: stack_isEmpty
Descripcion: Determina si la pila esta vacia o no
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- TRUE, si la pila esta vacia
- FALSE, si la pila esta llena
-----------------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *stack){
  if(!stack){
    return TRUE;
  }
  if(stack->top==-1){
    return TRUE;
  }
  return FALSE;
}

/*-----------------------------------------------------------------------------
Nombre: stack_isFull
Descripcion: Determina si la pila esta vacia o no
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- TRUE, si la pila esta vacia
- FALSE, si la pila esta llena
-----------------------------------------------------------------------------*/
Bool stack_isFull(const Stack *stack){
  if(!stack){
    return TRUE;
  }
  if(stack->top==MAXSTACK-1){
    return TRUE;
  }
  return FALSE;  
}

/*-----------------------------------------------------------------------------
Nombre: stack_print
Descripcion: Imprime los elementos de la pila
Argumentos de entrada:
1. f, puntero al fichero al que se imprime
2. stack, el puntero a la pila a liberar
Retorno:
- -1 en caso de error
- cont, el numero de caracteres escritos
-----------------------------------------------------------------------------*/
int stack_print(FILE* f, const Stack* stack){
  int cont=0;
  int i;
  if(!f || !stack){
    return -1;
  }
  for(i=cont=0; i!=stack->top+1; i++){
    cont+=element_print(f, stack->item[stack->top-i]);
    cont+=fprintf(f, "\n");
  }
  cont+=fprintf(f, "Stack size: %d\n", stack->top+1);
  return cont;
}

/*-----------------------------------------------------------------------------
Nombre: stack_size
Descripcion: Devuelve el tamaño de la pila
Argumentos de entrada:
1. stack, el puntero a la pila a liberar
Retorno:
- -1 en caso de error
- top+1, el tamaño de la pila
-----------------------------------------------------------------------------*/
int stack_size(const Stack*stack){
  if(!stack){
    return -1;
  }
  return stack->top+1;
}
