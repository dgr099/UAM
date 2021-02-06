#include <stdio.h>
#include "stack_fp.h"
#include "stack_types.h"
#include "node.h"

int main(){
  Stack *stack_s=NULL, *stack_n=NULL;
  Node *nodo=NULL;
  char *nombre=NULL;
  nodo=node_init();
  if(nodo==NULL){
    return 1;
  }
  stack_s=stack_init(string_free, string_copy, string_print);
  if(stack_s==NULL){
    node_free(nodo);
    return 1;
  }
  stack_n=stack_init(node_free, node_copy, node_print);
  if(stack_n==NULL){
    node_free(nodo);
    stack_free(stack_s);
    return 1;
  }
  if(node_setName(nodo, "first")==ERROR || node_setLabel(nodo, WHITE)==ERROR || node_setId(nodo, 111)==ERROR){
    node_free(nodo);
    stack_free(stack_s);
    stack_free(stack_n);
    return 1;    

  }
  if(stack_push(stack_n, nodo)==ERROR || stack_push(stack_s, node_getName(nodo))==ERROR){
    node_free(nodo);
    stack_free(stack_s);
    stack_free(stack_n);
    return 1;   
  }
  if(node_setName(nodo, "second")==ERROR || node_setLabel(nodo, WHITE)==ERROR || node_setId(nodo, 222)==ERROR){
    node_free(nodo);
    stack_free(stack_s);
    stack_free(stack_n);
    return 1;     
  }
  if(stack_push(stack_n, nodo)==ERROR || stack_push(stack_s, node_getName(nodo))==ERROR){
    node_free(nodo);
    stack_free(stack_s);
    stack_free(stack_n);
    return 1;   
  }
  fprintf(stdout, "Print Stack nodes:\n");
  stack_print(stdout, stack_n);
  fprintf(stdout, "Print Stack string:\n");
  stack_print(stdout, stack_s);
  fprintf(stdout, "Poping nodes...\n");
  while(stack_isEmpty(stack_n)!=TRUE){
    node_free(nodo);
    nodo=stack_pop(stack_n);
    node_print(stdout, nodo);
  }
  fprintf(stdout, "\nPoping node_names...\n");
  while(stack_isEmpty(stack_s)!=TRUE){
    nombre=stack_pop(stack_s);
    string_print(stdout, nombre);
    printf(" ");
    string_free(nombre);
  }
  printf("\n");
  node_free(nodo);
  stack_free(stack_s);
  stack_free(stack_n);  
  return 0;
}