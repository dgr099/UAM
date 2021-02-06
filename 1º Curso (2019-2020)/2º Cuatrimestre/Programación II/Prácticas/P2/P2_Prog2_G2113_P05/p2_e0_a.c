/**************************************************
Nombre del modulo: p2_e0_a.c
Descripcion: Manejo de elementos en una pila
Autor:  
Fecha: 03-03-20
Modulos propios que necesita:
- stack_fp.h
- stack_types.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include "stack_fp.h"
#include "stack_types.h"


/*=== Funciones =============================================================*/

int main(){
    char cadena[3]={'a', 'b', 'c'};
    int i=0, c;
    Stack *stack = NULL;
    char * car;
    stack=stack_init(char_free, char_copy, char_print);
    if(!stack){
        printf("Error");    
        return 0;
    }
    c=sizeof(cadena)/sizeof(char);
    for(i=0; i!=c; i++){
        if(stack_push(stack, &cadena[i])==ERROR){
            stack_free(stack);
            printf("Error"); 
            return 1;
        }
    }
    stack_print(stdout, stack);
    fprintf(stdout, "Stack size: %ld\n", stack_size(stack));
    while(stack_isEmpty(stack)!=TRUE){
        car=stack_pop(stack);
        if(car==NULL){
            stack_free(stack);
            printf("Error"); 
            return 1;
        }
        printf("Elemento extraido ");
        char_print(stdout, car);
        char_free(car);
        printf("\n");
    }
    fprintf(stdout, "Stack size: %ld\n", stack_size(stack));
    stack_free(stack);
    return 0;   
}
