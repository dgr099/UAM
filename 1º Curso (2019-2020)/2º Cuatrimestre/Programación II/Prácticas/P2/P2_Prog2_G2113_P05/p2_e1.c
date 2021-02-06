/**************************************************
Nombre del modulo: p2_e1.c
Descripcion: Inversion de palabras en pilas
Autor:  
Fecha: 06-03-20
Modulos propios que necesita:
- stack_fp.h
- stack_types.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"


/*=== Definiciones ==========================================================*/

#define MAX_F 100
#define MAX_P 30


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: reverseWords
Descripcion: Invierte las palabras de un string
Argumentos de entrada:
1. strout, el puntero al string de salida
2. strin, el puntero al string de entrada
Retorno:
- OK, si se ha terminado sin problemas
- ERROR en caso contrario
-----------------------------------------------------------------------------*/
Status reverseWords(char *strout, char *strin){
  char separador[]=" \n";
  char *palabra, *car;
  int top, i, z=0;
  Stack *stack;
  stack=stack_init(char_free, char_copy, char_print);
  if(stack==NULL){
    return ERROR;
  }
  palabra=strtok(strin, separador);
  while( palabra!= NULL ){
    top=strlen(palabra);
    for(i=0; i!=top; i++){
      if((stack_push(stack, &palabra[i]))==ERROR){
        stack_free(stack);
        return ERROR;
      }
    }
    while(stack_isEmpty(stack)!=TRUE){
    car=stack_pop(stack);
    strout[z]=*car;
    free(car);
    z++;
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
