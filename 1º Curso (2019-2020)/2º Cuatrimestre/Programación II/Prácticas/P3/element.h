/*
* File: element.h
* Author: Profesores de PROG2
*/
#ifndef ELEMENT_H
#define ELEMENT_H
#include "types.h"
typedef struct _Element Element;
Element* element_init();
void element_free(void *element);
Element* element_setInfo(Element* element, void* info);
void* element_getInfo(Element* element);
void* element_copy(const void* element);
Bool element_equals(const Element* element, const Element* element2);
int element_print(FILE* f, const void* element);
#endif /* ELESTACK_H */
