#include <stdio.h>
#ifndef QUEUE_H
#define QUEUE_H
#include "types.h"

/**
* @brief Structure to implement a queue. To be defined in queue_fp.c
*
**/
typedef struct _Queue Queue;
/**
* @brief Typedef for a function pointer to free a queue element
**/
typedef void (*free_element_function_type)(void*); /*tipo que retorna (void), (*nombre de la funcion), (parametros)*/
/**
* @brief Typedef for a function pointer to copy a queue element
**/
typedef void *(*copy_element_function_type)(const void*);
/**
* @brief Typedef for a function pointer to print a queue element
**/
typedef int (*print_element_function_type)(FILE *, const void*);
/**
* @brief This function initializes an empty queue.
*
13
* @param f1 A pointer to a funcion to free a element of the queue.
* @param f2 A pointer to a funcion to copy a element of the queue.
* @param f3 A pointer to a funcion to print a element of the queue.
* @return This function returns a pointer to the queue or a null
* pointer if insufficient memory is available to create the queue.
* */
Queue* queue_init(free_element_function_type f1, copy_element_function_type f2, print_element_function_type f3);
/**
* @brief This function frees all the memory used by the queue.
* @param s A pointer to the queue
* */
void queue_free(Queue *q);
/**
* @brief Returns whether the queue is empty
* @param s A pointer to the queue.
* @return TRUE or FALSE
*/
Bool queue_isEmpty(const Queue *q);
/**
* @brief This function is used to insert a element at the queue.
*
* A copy of the element is added to the queue container and the
* size of the queue is increased by 1. Time complexity: O(1).
* This function allocates memory for a copy of the element.
* @param s A pointer to the queue.
* @param ele A pointer to the element to be inserted
* @return This function returns OK on success or ERROR if
* insufficient memory is available to allocate the element.
* */
Status queue_insert(Queue *q, const void* pElem);
/**
* @brief This function is used to extract a element from the top of the queue.
*
* The size of the queue is decreased by 1. Time complexity: O(1).
* @param s A pointer to the queue.
* @return This function returns a pointer to the extracted element
* on success or null when the queue is empty.
* */
void * queue_extract(Queue *q);
/**
* @brief This function returns the size of the queue.
*
* Time complexity: O(1).
* @param s A pointer to the queue.
* @return the queue size
*/
int queue_size (const Queue *q);
/**
* @brief This function writes the elements of the queue to the stream.
* @param fp A pointer to the stream
* @param s A pointer to the element to the queue
* @return Upon successful return, these function returns the
* number of characters writted. The function returns a negative
* value if there was a problem writing to the file.
* */
int queue_print(FILE *pf, const Queue *q);
#endif
