#ifndef HASH_T
#define HASH_T 1

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "sym_info.h"

#define _XOPEN_SOURCE 500

typedef struct STRUCT_ENTRY_T {
	char *key;
	sym_info *value;
	struct STRUCT_ENTRY_T *next;
} entry_t;

typedef struct STRUCT_HASH_T {
	int size;
	entry_t **table;	
} hash_t;

/* Crear una tabla hash */
hash_t *hash_create(int size);

/* Liberar una tabla hash */
void hash_free(hash_t *hashtable);

/* Hashear una cadena */
int hash_hash(hash_t *hashtable, char *key);

/* Crear un par clave_valor */
entry_t *hash_newpair(char *key, sym_info *value);

/* Insertar un par clave_valor en una tabla hash */
void hash_set(hash_t *hashtable, char *key, sym_info *value);

/* Sacar un valor de una tabla hash */
sym_info *hash_get(hash_t *hashtable, char *key);

/*para obtener el size*/
int hash_get_size(hash_t *hashtable);

#endif