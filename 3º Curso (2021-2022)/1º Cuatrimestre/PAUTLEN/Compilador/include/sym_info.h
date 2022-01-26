#ifndef SYM_INFO_H
#define SYM_INFO_H 1
#include "alfa.h"

#define UNDEFINED -1    /* enteros no inicializados */

#define DOUBLE_ID -1
#define OUT_MEM -2

#define MIN_FILAS_VECTOR 1
#define MAX_FILAS_VECTOR 64

typedef enum
{
    VARIABLE,
    PARAMETRO,
    FUNCION
} Elemento;

typedef enum
{
    ESCALAR,
    VECTOR
} Categoria;

/* Informacion de un simbolo en la tabla */
typedef struct STRUCT_SYM_INFO
{
    char *lexema;       /* Identificador */

    Elemento elem;      /* Variable, Param o Funcion */
    Tipo tipo;          /* Boolean o Entero */
    Categoria catg;     /* Escalar o Vector */

    /* Escalares */
    int valor;
    
    /* Para vectores */
    int size;           /* Num filas [1, 64] */

    /* Para funciones */
    int num_params;     /* Nº parametros */
    int num_vars_loc;   /* Nº variables locales */

    /* Variables LOCALES */
    int is_var_loc;     /* Para variables locales */
    int pos_var_loc;    /* (empezando en 1) */

    /* Para parametros */
    int pos_param;      /* (empezando en 0) */
} sym_info;

/**
 * @param lexema        ID del simbolos
 * @param elem          Tipo de elemento (VARIABLE, PARAMETRO, FUNCION)
 * @param tipo          INT o BOOLEAN
 * @param catg          Categoria del elemento (ESCALAR, VECTOR)
 * @param e1            Si ESCALAR -> Valor, VECTOR -> Longitud, FUNCION -> Num. parametros
 * @param e2            Si PARAMETRO -> Posicion en call, VARIABLE LOCAL -> Posicion en declaraciones 
 *                      de funcion, FUNCION -> Num. variables locales 
 * @param is_var_loc    VARIABLE LOCAL -> 1, OTRO -> 0
 * 
 * @return Puntero a info de simbolo 
 */
sym_info *sym_info_create(const char* lexema, Elemento elem, Tipo tipo, Categoria catg, int e1, int e2);



/**
 * Libera la memoria del simbolo
 *
 * @param sym Simbolo
 */
void sym_info_free(sym_info *sym);

#endif