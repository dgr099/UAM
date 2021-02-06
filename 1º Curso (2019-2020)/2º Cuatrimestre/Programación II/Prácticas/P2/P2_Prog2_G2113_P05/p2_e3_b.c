/******************************************************************************
Nombre del módulo: p2_e3_b.c
Descripción: Repeticion del ejercicio 0a con nuevo TAD pila
Autor:  
Fecha: 12/03/20
Modulos propios que necesita:
  -element.h
  -stack.h
Notas:
Modificaciones:
Mejoras pendientes:
******************************************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "stack.h"

/*=== Funciones =============================================================*/

int main(){
  Stack *stack;
  Element *element;
  if((element=element_init())==NULL || !(stack=stack_init())){
    return ERROR;
  }
  element_setInfo(element, "a");
  if(stack_push(stack, element)==ERROR){
    stack_free(stack);
    element_free(element);
    return 1;
  }
  element_setInfo(element, "b");
  if(stack_push(stack, element)==ERROR){
    stack_free(stack);
    element_free(element);
    return 1;
  }
  element_setInfo(element, "c");
  if(stack_push(stack, element)==ERROR){
    stack_free(stack);
    element_free(element);
    return 1;
  }
  element_free(element);
  stack_print(stdout, stack);
  while(stack_isEmpty(stack)!=TRUE){
    if(!(element=stack_pop(stack))){
      stack_free(stack);
      return 1;
    }
    printf("El elemento extraido es: %s\n", (char*)element_getInfo(element));
    element_free(element);
  }
  stack_print(stdout, stack);
  stack_free(stack);
  return 0;
}
