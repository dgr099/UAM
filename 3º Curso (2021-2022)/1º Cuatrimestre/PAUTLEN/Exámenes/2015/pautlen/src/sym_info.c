#include "sym_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SIMBOLOS */
sym_info *sym_info_create(const char* lexema, Elemento elem, Tipo tipo, Categoria catg, int e1, int e2)
{
    sym_info* sym = NULL;
    
    if ((sym = (sym_info*) malloc(sizeof(sym_info)))==NULL){
        return NULL;
    }
    else{
        if(!(sym->lexema=(char*)malloc((strlen(lexema)+1)*sizeof(char)))){
            free(sym);
            return NULL;
        }
        strcpy(sym->lexema, lexema);
        sym->elem = elem;
        sym->tipo = tipo;
        sym->catg = catg;
        sym->valor = UNDEFINED;
        sym->size = UNDEFINED;
        sym->num_params = UNDEFINED;
        sym->num_vars_loc = UNDEFINED;
        sym->is_var_loc = UNDEFINED;
        sym->pos_var_loc = UNDEFINED;
        sym->pos_param = UNDEFINED;
        /* e1 valor si escalar, long si vector, número de parámetros si función */
        /* e2 pos en call si parámetro, pos de declaración si variable local, nº de var loc si función */
        if (elem == FUNCION) {
            sym->num_params = e1;
            sym->num_vars_loc = e2;
        } else if (elem == PARAMETRO)
            sym->pos_param = e2;
        if (catg == ESCALAR) {
            sym->valor = e1;
            sym->size = 1;
        } else if (catg == VECTOR) {
            sym->size = e1;
        }
    }
    return sym;
}

void sym_info_free(sym_info *sym)
{
    if (sym) {
        if (sym->lexema)
            free(sym->lexema);
        free(sym);
    }
}

