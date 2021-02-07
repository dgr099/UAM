/**
 * @file list.h
 * @author Programming II Teaching Team
 * @date 15 Mar 2020
 * @brief Public interface for a Linked List implementation.
 *
 * The List admits arbitrary elements, received as pointers to void. It is 
 * necessary to provide functions to free, copy and print an element when
 * creating the List (see documentation).
 *
 * This List implementation currently provides the following functionality:
 *
 * - Create and destroy a List.
 * - Check if a List is empty.
 * - Push an element into the front or back positions. 
 * - Pop an element from the front or back positions. 
 * - Get the number of elements in a List.
 * - Print a List.
 *
 * Other desired funtionality not yet implemented includes:
 * 
 * - Accessing the front and back elements without extracting them.
 * - Inserting to and extracting from arbitrary positions. 
 */

#ifndef LIST_H
#define	LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/**
 * List type definition: a list of arbitrary elements.
 */
typedef struct _List List;

/**
 * P_ele_free type definition: pointer to a function that frees a List element.
 */
typedef void (*P_ele_free)(void*);

/**
 * P_ele_copy type definition: pointer to a function that copies a List element.
 * It is assumed that this function: 
 * (1) allocates memory for the new element; 
 * (2) copies the element onto the new element; and
 * (3) returns the pointer to the new element. 
 */
typedef void *(*P_ele_copy)(const void*);

/**
 * P_ele_print type definition: pointer to a function that prints a List element to
 * an output stream. It is assumed that this function returns:
 * (1) the number of characters printed upon success; or
 * (2) a negative number in case of error. 
 */
typedef int (*P_ele_print)(FILE *, const void*);

/**
 * @brief Public function that creates a new List.
 *
 * Allocates memory for the new List. When creating a List it is necessary to 
 * specify the pointers to functions that:
 * - Free a List element.
 * - Copy a List element.
 * - Print a List element.
 *
 * @param f1 Pointer to the function that frees a List element. 
 * @param f2 Pointer to the function that copies a List element. 
 * @param f3 Pointer to the function that prints a List element.
 *
 * @return Returns the address of the new list, or NULL in case of error.  
 */
List *list_new(P_ele_free f1, P_ele_copy f2, P_ele_print f3);

/**
 * @brief Public function that checks if a List is empty.
 *
 * Note that the return value is TRUE for a NULL List. 
 * 
 * @param pl Pointer to the List.  
 *
 * @return Boolean value TRUE if the list is empty or NULL, Boolean value FALSE
 * otherwise.  
 */
Boolean list_isEmpty(const List *pl);

/**
 * @brief Public function that pushes an element into the front position of a 
 * List. 
 *
 * Inserts into the front position a copy of the element received as argument. 
 * This copy is obtained by calling the function specified when creating the
 * List.  
 * 
 * @param pl Pointer to the List.  
 * @param e Pointer to the element to be inserted into the List. 
 *
 * @return Status value OK if the insertion could be done, Status value ERROR 
 * otherwise.  
 */
Status list_pushFront(List *pl, const void *e);

/**
 * @brief Public function that pushes an element into the back position of a 
 * List. 
 *
 * Inserts into the back position a copy of the element received as argument. 
 * This copy is obtained by calling the function specified when creating the
 * List.  
 *
 * Note that it is necessary to traverse the list in order to obtain the 
 * insert position, so this operation is linear in the number of List elements.
 * 
 * @param pl Pointer to the List.  
 * @param e Pointer to the element to be inserted into the List. 
 *
 * @return Status value OK if the insertion could be done, Status value ERROR 
 * otherwise.  
 */
Status list_pushBack(List *pl, const void *e);

/**
 * @brief Public function that pops the front element from a List. 
 *
 * Extracts the front element from the List, returning a pointer to it. 
 * 
 * @param pl Pointer to the List.  
 *
 * @return Pointer to the extracted element, or NULL in case of error. 
 */
void *list_popFront(List *pl);

/**
 * @brief Public function that pops the back element from a List. 
 *
 * Extracts the element element from the List, returning a pointer to it. 
 * 
 * Note that it is necessary to traverse the list in order to obtain the 
 * extract position, so this operation is linear in the number of List elements.
 * 
 * @param pl Pointer to the List.  
 *
 * @return Pointer to the extracted element, NULL if the List is empty or NULL. 
 */
void *list_popBack(List *pl);

/**
 * @brief Public function that frees a List. 
 *
 * Frees all the memory allocated for the List. 
 * 
 * @param pl Pointer to the List.  
 */
void list_free(List *pl);

/**
 * @brief Public function that returns the number of elements in a List. 
 *
 * Note that the number of elements is not stored in the data structure, and the
 * List must be traversed in order to obtain its size. So this operation is linear
 * in the number of List elements.   
 * 
 * @param pl Pointer to the List.  
 *
 * @return Returns the number of elements in the List, or -1 if the List is NULL. 
 */
int list_size(const List *pl);

/**
 * @brief Public function that prints the contenf of a List. 
 *
 * Prints all the elements in the List, from front to rear, to an output stream.
 * To print an element this function calls the function specified when creating 
 * the List, P_ele_print.      
 *
 * Note that this function simply calls the P_ele_print function for each List
 * element, without printing any additional information. Any desired format must
 * be included in the P_ele_print function. 
 * 
 * @param fp Output stream.  
 * @param pl Pointer to the List.  
 *
 * @return The sum of the return values of all the calls to P_ele_print if these
 * values are all positive; the first negative value encountered otherwise. If the
 * function P_ele_print is well constructed, this means that, upon successful return,
 * this function returns the number of characters printed, and a negative value if 
 * an error occurs.  
 */
int list_print(FILE *fp, const List *pl);

#endif	/* LIST_H */
