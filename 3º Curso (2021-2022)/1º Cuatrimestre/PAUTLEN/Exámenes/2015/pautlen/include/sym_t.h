#ifndef SYM_T_H
#define SYM_T_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_t.h"

/* Tabla de simbolos */
typedef struct STRUCT_SYM_T {
    /* Tabla de simbolos Ambito Global */
    hash_t* tabla_global;
    /* Tabla de simbolos Ambito Local (funcion) */
    hash_t* tabla_local;
    /* todos los símbolos globales */
    char** symbolsGlobal;
    /* todos los símbolos locales */
    char** symbolsLocal;
    /* tamaño de todos los símbolos globales */
    int tamG;
    /* tamaño de todos los símbolos locales */
    int tamL;
} sym_t;


/*************************************/
/*    FUNCIONES TABLA DE SIMBOLOS    */
/*************************************/

/**
 * Inicializa la tabla de simbolos
 * 
 * @return Puntero a tabla de simbolos
 */
sym_t *sym_t_create();

/**
 * Libera la memoria de la tabla de simbolos
 *
 * @param tabla Tabla de simbolos
 */
void sym_t_free();

/**
 * Crea la tabla local de la tabla de simbolos
 *
 * @param key string identificador de ámbito local
 * @param value valor de ámbito local
 */
void open_scope(char* key, int value, Tipo tipo);

/**
 * Cierra la tabla local de la tabla de simbolos
 * 
 */
void close_scope();

/**
 * Anyade un simbolo al hash local, si existe. De lo contrario,
 * anyade al hash global.
 * 
 * @param sym   Simbolo
 * @return -1 si no hay tablas inicializadas
 */
int sym_t_add_symb(sym_info *sym);

/**
 * Obtiene el simbolo en funcion de su ID.
 *
 * @param id    String ID de lo leido
 * @return Puntero a simbolo de la tabla de simbolos
 */
sym_info* sym_t_get_symb(char *id);

/**
 * Función para checkear si puede insertar un valor
 */
sym_info* sym_t_check(char *id);

char **sym_t_getLocalSymbols();

char **sym_t_getGlobalSymbols();

sym_info* sym_t_get_symb_local(char *id);

#endif