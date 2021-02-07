#include "types.h"
#ifndef INT_H
#define INT_H
void*    int_copy(const void* ent);
void    int_free(void* ent);
int  int_print(FILE *f, const void* ent);
#endif