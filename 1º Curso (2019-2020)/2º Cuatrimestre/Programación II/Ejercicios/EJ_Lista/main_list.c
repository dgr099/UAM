#include <stdio.h>
#include <stdlib.h>
#include "int.h"
#include "list.h"

int main(){
	List *lista1, *lista2, *lista3;
    int i, *aux;
    fprintf(stdout, "Creating list 1... ");
	if(!(lista1=list_new(int_free, int_copy, int_print))){
        return 1;
    }
    fprintf(stdout, "Size = %d\n", list_size(lista1));
    fprintf(stdout, "Inserting elements into list...\n");
    for(i=0; i!=11; i++){
        if(i%2==0){
            if(list_pushFront(lista1, &i)==ERROR){
                list_free(lista1);
                return 1;
            }
        }
    }
    fprintf(stdout, "Printing list 1:\n");
    fprintf(stdout, "Size = %d. ", list_size(lista1));
    fprintf(stdout, "Elements: ");
    list_print(stdout, lista1);
    fprintf(stdout, "\nCreating list 2... ");
	if(!(lista2=list_new(int_free, int_copy, int_print))){
        list_free(lista1);
        return 1;
    }
    printf("Size = %d\n", list_size(lista2));
    fprintf(stdout, "Inserting elements into list...\n");
    for(i=1; i!=10; i++){
        if(i%2!=0){
            if(list_pushFront(lista2, &i)==ERROR){
                list_free(lista1);
                list_free(lista2);
                return 1;
            }           
        }
    }
    fprintf(stdout, "Printing list 2:\n");
    fprintf(stdout, "Size = %d. ", list_size(lista2));
    fprintf(stdout, "Elements: ");
    list_print(stdout, lista2);
    fprintf(stdout, "\nCreating list 3... ");
	if(!(lista3=list_new(int_free, int_copy, int_print))){
        list_free(lista1);
        list_free(lista2);
        return 1;
    }
    fprintf(stdout, "Size = %d\n", list_size(lista3));
    fprintf(stdout, "Combining elements from list 1 and list 2 into list 3...\n");
    for(i=0; i!=11; i++){
        if(i%2==0){
            aux=list_popFront(lista1);
            fprintf(stdout, "Extracted element from list 1: ");
        }
        else{
            aux=list_popFront(lista2);
            fprintf(stdout, "Extracted element from list 2: ");
        }
        int_print(stdout, aux);
        fprintf(stdout, "\n");
        if(list_pushFront(lista3, aux)==ERROR){
            list_free(lista1);
            list_free(lista2);
            list_free(lista3);
            return 1;
        }
        free(aux);        
    }
    fprintf(stdout, "Printing list 1:\n");
    fprintf(stdout, "Size = %d. Elements: ", list_size(lista1));
    list_print(stdout, lista1);
    fprintf(stdout, "\nPrinting list 2:\n");
    fprintf(stdout, "Size = %d. Elements: ", list_size(lista2));
    list_print(stdout, lista2);
    fprintf(stdout, "\nPrinting list 3:\n"); 
    fprintf(stdout, "Size = %d. Elements: ", list_size(lista3));
    list_print(stdout, lista3);
    fprintf(stdout, "\nFreeing memory..."); 
    list_free(lista1);
    list_free(lista2);
    list_free(lista3);
    return 0;     

}