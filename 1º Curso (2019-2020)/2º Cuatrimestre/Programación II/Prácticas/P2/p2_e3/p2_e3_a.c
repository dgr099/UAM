/******************************************************************************
Nombre del módulo: modelo.c
Descripción: 
Autor:  
Fecha: 06/03/20
Modulos propios que necesita:
  -stack.c
  -element.c
Notas:
Modificaciones:
Mejoras pendientes:
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "stack.h"
Status reverseWords(char *strout, char *strin){
  char separador[]=" \n";
  char *palabra;
  Element *element;
  int top, i, z=0;
  Stack *stack;
  stack=stack_init();
  element=element_init();
  if(stack==NULL || !element){
    return ERROR;
  }
  palabra=strtok(strin, separador);
  top=strlen(palabra);
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
  }
  while((palabra=strtok(NULL, separador))!=NULL){
  element=element_init();
  strout[z]=' ';
  z++;
  top=strlen(palabra);
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
  }    
  }
  /*while((palabra=strtok(NULL, separador))!=NULL){
    strout[z]=' ';
    z++;
    top=strlen(palabra);
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
    }  
  }*/
  stack_free(stack);
  return OK;
}

int main(int argc,char **argv){
  char *frase_inv;
  if(argc<2){
    printf("Error, pruebe a escribir ./ejecutable frase_a_invertir");
    return 1;
  }
  frase_inv=calloc(strlen(argv[1]), sizeof(char));
  reverseWords(frase_inv, argv[1]);
  printf("%s\n", frase_inv);
  free(frase_inv);
  return 0;
}
