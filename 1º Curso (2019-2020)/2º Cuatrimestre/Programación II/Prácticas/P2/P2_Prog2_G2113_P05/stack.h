/**
* @file stack_fp.h
* @author Profesores Prog2
* @date 10 Dec 2018
* @version 1.0
* @brief Stack library
*
* @details Stack interface
*
* @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
*/
/*
* File: stack.h
* Author: Profesores de PROG2
*/
#ifndef STACK_H
#define STACK_H
#include "element.h"
/**
* @brief Structure to implement a stack.
*
**/
typedef struct _Stack Stack;
/**
* @brief This function create a stack
*
* */
Stack * stack_init ();
/**
* @brief This function free a stack
* @param  stack stack that you want to free
* */
void stack_free(Stack *stack);
/**
* @brief This function push an element into the stack
* @param  stack the stack in which you want to push an element
* @param  element the element you want to push
* @return ok or error
* */
Status stack_push(Stack *stack, const Element *element);
/**
* @brief This function pop an element of the stack
* @param  stack the stack
* @return the addres of the element
* */
Element * stack_pop(Stack *stack);
/**
* @brief This function return the top of an stack
* @param  * the stack
* @return the addres of the element in the top
* */
Element * stack_top(const Stack *stack);
/**
* @brief This function is use to see if an stack is empty
* @param  stack the stack
* @return True if the stack is empty false otherwise
* */
Bool stack_isEmpty(const Stack *stack);
/**
* @brief This function is use to see if an stack is full
* @param  stack the stack
* @return True if the stack is empty false otherwise
* */
Bool stack_isFull(const Stack *stack);
/**
* @brief This function is use to print a stack
* @param  stack the stack
* @param f the file in which you want to print the stack
* */
int stack_print(FILE* f, const Stack* stack);
/**
* @brief This function returns the size of a stack
* @param  stack the stack
* @return top+1, the size of the stack
* */
int stack_size(const Stack *stack);
#endif /* STACK_H */
