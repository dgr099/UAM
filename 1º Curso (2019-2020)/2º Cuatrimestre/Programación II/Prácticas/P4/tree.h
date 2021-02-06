#ifndef TREE_H
#define TREE_H

#include "types.h"
#include "node.h"

/**
 * BSTree type definition: a binary search of arbitrary elements.
 */
typedef struct _BSTree BSTree;

/* Tipos de los punteros a función soportados por el árbol */

/**
 * Pointer to a function that frees a Tree element.
 */
typedef void (*destroy_element_function_type)(void*);

/**
 * P_ele_copy type definition: pointer to a function that copies a tree element.
 * It is assumed that this function:
 * (1) allocates memory for the new element;
 * (2) copies the element onto the new element; and
 * (3) returns the pointer to the new element or NULL .
 */
typedef void *(*copy_element_function_type)(const void*);

/**
 * P_ele_print type definition: pointer to a function that prints a tree element to
 * an output stream. It is assumed that this function returns:
 * (1) the number of characters printed upon success; or
 * (2) a negative number in case of error.
 */
typedef int (*print_element_function_type)(FILE *, const void*);

/**
 * P_ele_cmp type definition: pointer to a function that compares two elements of a Tree
 * It returns an integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
typedef int (*cmp_element_function_type)(const void*, const void*);

/**
 * @brief Public function that creates a new BSTree.
 *
 * Allocates memory for the new Tree. When creating a Tree it is necessary to
 * specify the pointers to functions that:
 * - Free a Tree element.
 * - Copy a Tree element.
 * - Print a Tree element.
 * - Compare two elements
 * 
 * @param f1 Pointer to the function that frees a Tree element.
 * @param f2 Pointer to the function that copies a Tree element.
 * @param f3 Pointer to the function that prints a Tree element.
 * @param f4 Pointer to a function that compare two Tree elements
 *
 * @return Returns the address of the new Tree, or NULL in case of error.
 */
BSTree* tree_init (destroy_element_function_type f1,
copy_element_function_type f2,
print_element_function_type f3,
cmp_element_function_type f4);

/**
 * @brief Public function that frees a Tree.
 *
 * Frees all the memory allocated for the Tree.
 *
 * @param pl Pointer to the Tree.
 */
void tree_destroy (BSTree *tree);

/**
 * @brief Public function that inserts an element into a Binary Search Tree.
 *
 * Inserts as a leaf a copy of the element received as argument.
 * This copy is obtained by calling the function specified when creating the
 * Tree.
 * 
 * Note that it is necessary to descend the subtree to obtain the
 * insert position. So this operation is logarithm with the length of the path
 * from the leaf to the root.
 *
 * @param pl Pointer to the Tree.
 * @param e Pointer to the element to be inserted into the Tree.
 * 
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
Status tree_insert (BSTree *tree, const void *elem);

/**
 * @brief Public function that checks if a Tree is empty.
 * 
 * Note that the return value is TRUE for a NULL Tree.
 * 
 * @param pl Pointer to the Tree.
 * 
 * @return Bool value TRUE if the Tree is empty or NULL, Bool value FALSE
 * otherwise.
 */
Bool tree_isEmpty (const BSTree *tree);

/**
 * @brief Public function that returns the Tree's depth
 * 
 * Note that the return value is TRUE for a NULL Tree.
 * 
 * @param pl Pointer to the Tree.
 * 
 * @return -1 if the tree is empty.
 */
int tree_depth (const BSTree *tree);

/**
 * @brief Public functions that prints the content of a Tree.
 * 
 * Prints all the elements in the Tree to an output stream.
 * To print an element this function calls the function specified when creating
 * the Tree, P_ele_print.
 * 
 * Note that this function simply calls the P_ele_print function for each Tree
 * element, without printing any additional information. Any desired format must
 * be included in the P_ele_print function.
 * 
 * - tree_preOrder : Traverse the tree with preOrder algorithm
 * - tree_inOrder: Traverse the tree with the inOrder algorithm;
 * - tree PostOrder : Traverse the tree with the postOrder algorithm
 * 
 * @param fp Output stream.
 * @param pl Pointer to the Tree.
 * 
 * @return The sum of the return values of all the calls to P_ele_print if these
 * values are all positive; the first negative value encountered otherwise. If the
 * function P_ele_print is well constructed, this means that, upon successful return,
 * this function returns the number of characters printed, and a negative value if
 * an error occurs.
*/
void tree_preOrder(FILE *f, const BSTree *tree);
void tree_inOrder(FILE *f, const BSTree *tree);
void tree_postOrder(FILE *f, const BSTree *tree);


#endif
