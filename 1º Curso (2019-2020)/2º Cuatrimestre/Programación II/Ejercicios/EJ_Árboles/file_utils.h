#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include "tree.h"
#include "types.h"

/*** conversion functions ***/
/* function type to convert strings to elements of the appropriate type */
/* the functions should allocate memory for the element */
typedef void *(*elem_from_string)(const char *str);
/* convert string to integer pointer */
void *str2int(const char *str);
/* convert string to string, i.e duplicate string*/
void *str2str(const char *str);
/* convert string to char pointer */
void *str2chr(const char *str);

/*** file functions */
Status read_tree_from_file(BSTree *tree, char *filename,
                           elem_from_string convert);
BSTree *create_tree_from_file(char *filename, char type);

/* generic function type to process an element */
typedef void (*process_element)(const void *element);

/* for debugging */
void test_file_conversion();

#endif