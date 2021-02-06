/**
 * @file list.h
 * @author Programming II Teaching Team
 * @date 6 April 2020
 * @brief Public interface for a Linked List implementation.
 *
 * The List admits arbitrary elements, received as pointers to void. It is
 * necessary to provide functions to free, copy and print an element,
 * and a function to compare two elements when
 * creating the List (see documentation).
 *
 * This List implementation currently provides the following functionality:
 *
 * - Create and destroy a List.
 * - Check if a List is empty.
 * - Push an element into the front or back positions.
 * - Push an element in an ordered list.
 * - Pop an element from the front or back positions.
 * - Get the number of elements in a List.
 * - Get the element that occupies the i-position.
 * - Search an element in the list
 * - Print a List.
 *
 * Other desired funtionality not yet implemented includes:
 *
 * - Accessing the front and back elements without extracting them.
 * - Inserting to and extracting from arbitrary positions.
 */

#ifndef LIST_H
#define	LIST_H

#include "types.h"
#include <stdio.h>

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
typedef int (*P_ele_print)(FILE *, const void *);


/**
 * P_ele_cmp type definition: pointer to a function that compares two elements of a List
 *  It returns an integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or  be greater than s2.
 */
typedef int (*P_ele_cmp)(const void *, const void *);


/**
 * @brief Public function that creates a new List.
 *
 * Allocates memory for the new List. When creating a List it is necessary to
 * specify the pointers to functions that:
 * - Free a List element.
 * - Copy a List element.
 * - Print a List element.
 * - Compare two List elements
 *
 * @param f1 Pointer to the function that frees a List element.
 * @param f2 Pointer to the function that copies a List element.
 * @param f3 Pointer to the function that prints a List element.
 * @param f4 Pointer to the function that compares two List elements
 *
 * @return Returns the address of the new list, or NULL in case of error.
 */
List *list_new(P_ele_free f1, P_ele_copy f2, P_ele_print f3, P_ele_cmp f4);

/**
 * @brief Public function that checks if a List is empty.
 *
 * Note that the return value is TRUE for a NULL List.
 *
 * @param pl Pointer to the List.
 *
 * @return Bool value TRUE if the list is empty or NULL, Bool value FALSE
 * otherwise.
 */
Bool list_isEmpty(const List *pl);

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
 * @brief Public function that pushes an element into an ordered list.
 *
 * Inserts in its position a copy of the element received as argument.
 * This copy is obtained by calling the function specified when creating the
 * List.
 *
 * Note that it is necessary to traverse the list in order to obtain the
 * insert position, so this operation is linear in the number of List elements.
 *
 * @param pl Pointer to the List.
 * @param e Pointer to the element to be inserted into the List.
 * @param order Must takes a positive value for a crescent list and negative
 *  value for decrescent list.
 *
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
Status list_pushOrder (List *pl, const void *e, int order);

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
 * @brief Public function that prints the content of a List.
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


/**
 * @brief Public function that returns the position of an element in the list.
 *
 * Note that it is necessary to traverse the list in order to obtain the
 * element position, so this operation is linear in the number of List elements,
 * O(n).
 *
 * @param pl Pointer to the List.
 * @param ele Pointer to the element.
 *
 * @return Returns the position of the element, or -1 if ele is not into the list.
 */
int list_getPositionElement (const List *pl, const void *ele);


/**
 * @brief Public function that returns the element in the position i.
 *
 * Note that this function returns the element, NOT a copy of the element.
 * Note that it is necessary to traverse the list in order to obtain the
 * element, so this operation is linear in the number of List elements,
 * O(n).
 *
 * @param pl Pointer to the List.
 * @param i Position of the element to be returned
 *
 * @return Returns the element, or NULL.
 */
void * list_getElementInPos (const List *pl, int i);

#endif	/* LIST_H */
