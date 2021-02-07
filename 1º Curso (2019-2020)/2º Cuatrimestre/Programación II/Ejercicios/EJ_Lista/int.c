#include "stdio.h"
#include "stdlib.h"
#include "types.h"
void*    int_copy(const void* ent){
    int* lol;
    const int* z;
    if(!ent){
        return NULL;
    }
    z=ent;
    lol=malloc(sizeof(int));
    *lol=*z;
    return lol;
}

void    int_free(void* ent){
    if(!ent){
        return;
    }
    free(ent);
    return;
}

int  int_print(FILE *f, const void* ent){
    const int *z=ent;
    if(!z){
        return -1;
    }
    return (fprintf(f, "%d ", *z));
}