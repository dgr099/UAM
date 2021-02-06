#include <stdio.h>
#include "string.h"
#include "stack_fp.h"
#include "stack_types.h"
#define MAX_F 100
#define MAX_P 30
/**
* @brief: Reverse the words of an input string to an output string.
* The words in the input string are separated by a space character.
* The strings may not overlap, and the destination string strout
* must be large enough to receive the inverted expression.
*
* @param strout, Pointer to the output buffer
* @param strin, Pointer to the input expression
* @return The function returns OK or ERROR
**/
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
      stack_push(stack, &palabra[i]);
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
  frase_inv=calloc(strlen(argv[1]), sizeof(char));
  reverseWords(frase_inv, argv[1]);
  printf("%s\n", frase_inv);
  free(frase_inv);
  return 0;
}
