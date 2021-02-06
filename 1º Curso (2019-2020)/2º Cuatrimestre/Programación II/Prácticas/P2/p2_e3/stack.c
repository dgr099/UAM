#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "element.h"
#define MAXSTACK 1024
struct _Stack {
int top;
Element * item[MAXSTACK];
};

Stack* stack_init (){
  Stack *stack;
  if((stack=(Stack*)calloc(1, sizeof(Stack)))==NULL){
    return NULL;
  }
  stack->top=-1;
  return stack;
}

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

Element* stack_top(const Stack *stack){
  if(!stack){
    return NULL;
  }
  return stack->item[stack->top];
}

Bool stack_isEmpty(const Stack *stack){
  if(!stack){
    return TRUE;
  }
  if(stack->top==-1){
    return TRUE;
  }
  return FALSE;
}

Bool stack_isFull(const Stack *stack){
  if(!stack){
    return TRUE;
  }
  if(stack->top==MAXSTACK-1){
    return TRUE;
  }
  return FALSE;  
}

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