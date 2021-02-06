#include <stdio.h>
#include "stack_fp.h"
#include "stack_types.h"

int main(){
    char cadena[3]={'a', 'b', 'c'};
    Status cod;
    int i=0, c, tam;
    Stack *stack = NULL;
    char * lol;
    stack=stack_init(char_free, char_copy, char_print);
    if(!stack){
        printf("Error");    
        return 0;
    }
    c=sizeof(cadena)/sizeof(char);
    for(i=0; i!=c; i++){
        cod=stack_push(stack, &cadena[i]);
        if(cod==ERROR){
            stack_free(stack);
            printf("Error"); 
            return 1;
        }
    }
    fprintf(stdout, "Tamño: %ld\n", stack_size(stack));
    cod=stack_print(stdout, stack);
    if(cod==ERROR){
        stack_free(stack);
        printf("Error"); 
        return 1;
    }
    lol=stack_pop(stack);
    if(lol==NULL){
        stack_free(stack);
        printf("Error"); 
        return 1;
    }
    printf("Elemento extraido ");
    char_print(stdout, lol);
    
    fprintf(stdout, "\nTamño: %ld\n", stack_size(stack));
    cod=stack_print(stdout, stack);
    if(cod==ERROR){
        stack_free(stack);
        printf("Error"); 
        return 1;
    }
    char_free(lol);
    stack_free(stack);
    return 0;   
}