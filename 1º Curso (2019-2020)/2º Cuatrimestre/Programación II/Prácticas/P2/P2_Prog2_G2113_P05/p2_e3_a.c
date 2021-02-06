/******************************************************************************
Nombre del modulo: p2_e3_a.c
Descripcion: Inversion de palabras en pilas con el TAD element
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
#include <string.h>
#include "element.h"
#include "stack.h"


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: reverseWords
Descripcion: Invierte las palabras de un string
Argumentos de entrada:
1. strout, puntero al string de salida
2. strin, puntero al string de entrada
Retorno:
- TRUE, si el caracter es un operador
- FALSE, si el caracter no es un operador
-----------------------------------------------------------------------------*/
Status reverseWords(char *strout, char *strin){
  char separador[]=" \n";
  char *palabra;
  Element *element;
  int top, i, z=0;
  Stack *stack;
  stack=stack_init();
  if(!stack){
    return ERROR;
  }
  palabra=strtok(strin, separador);
  /*top=strlen(palabra);
  for(i=0; i!=top; i++){
    element_setInfo(element, &palabra[i]);
    stack_push(stack, element);
  }
  element_free(element);
  while(stack_isEmpty(stack)!=TRUE){
    element=stack_pop(stack);
    strout[z]=*((char*)element_getInfo(element));
    z++;
    element_free(element);
  }*/
  while(palabra!=NULL){
    if((element=element_init())==NULL){
      stack_free(stack);
      return ERROR;
    }
    top=strlen(palabra);
    for(i=0; i!=top; i++){
      element_setInfo(element, &palabra[i]);
      if((stack_push(stack, element))==ERROR){
        stack_free(stack);
        element_free(element);
        return ERROR;
      }
    }
    element_free(element);
    while(stack_isEmpty(stack)!=TRUE){
      element=stack_pop(stack);
      strout[z]=*((char*)element_getInfo(element));
      z++;
      element_free(element);
    }
    if((palabra=strtok(NULL, separador))!=NULL){
      strout[z]=' ';
      z++;
    }
  }
  stack_free(stack);
  return OK;
}


int main(int argc,char **argv){
  char *frase_inv;
  if(argc<2){
    printf("Error, pruebe a escribir ./ejecutable frase_a_invertir");
    return 1;
  }
  frase_inv=calloc(strlen(argv[1]) + 1, sizeof(char));
  if((reverseWords(frase_inv, argv[1]))!=ERROR){
    printf("%s\n", frase_inv);
    free(frase_inv);
    return 0;
  }
  printf("Error en la ejecución del programa");
  free(frase_inv);
  return 1;
}
