#include "hash_t.h"
#include <string.h>


hash_t *hash_create(int size )
{
	hash_t *hashtable = NULL;
	int i;

	if (size < 1) 
        return NULL;

	if ((hashtable = (hash_t*)malloc(sizeof(hash_t))) == NULL)
		return NULL;

	if (!(hashtable->table = (entry_t**)malloc(sizeof(entry_t*) * size)))
		return NULL;

	for (i = 0; i < size; i++)
		hashtable->table[i] = NULL;

	hashtable->size = size;

	return hashtable;
}

void hash_free(hash_t *hashtable)
{
    if (hashtable->table) { /*si hay tabla*/
        for (int i = 0; i < hashtable->size; i++) { /*por cada pos de la yabla*/
			entry_t* entrada= hashtable->table[i];
			if(entrada!=NULL){
				if(entrada->value->elem!=FUNCION){
					sym_info_free(entrada->value);
					free(entrada->key);
            		free(entrada);
				}
			}
        }
    }
	free(hashtable->table);
    free(hashtable);
}

int hash_hash(hash_t *hashtable, char *key)
{
	unsigned long int hashval=0;
	int len =  strlen(key);
	for (int i=0; hashval < ULONG_MAX && i < len; i++) {
		hashval = hashval << 8; /*hashval=hashval*256*/
		hashval += key[i]; /*hashvla+=valor ascii de la pos i de la cadena*/
	}
	return hashval % hashtable->size;
}


entry_t *hash_newpair(char *key, sym_info *value)
{
	entry_t *newpair;
	if (!(newpair = malloc(sizeof(entry_t))))
		return NULL;
	
	if(!(newpair->key = (char*)calloc(strlen(key)+1, sizeof(char))))
		return NULL;
	if(!strcpy(newpair->key, key))
		return NULL;

	if(!(newpair->value = value))
		return NULL;

	newpair->next = NULL;

	return newpair;
}


void hash_set(hash_t *hashtable, char *key, sym_info *value)
{
	int index = 0;
	struct STRUCT_ENTRY_T *newpair = NULL;
	struct STRUCT_ENTRY_T *next = NULL;
	struct STRUCT_ENTRY_T *last = NULL;
	index = hash_hash(hashtable, key);

	next = hashtable->table[index];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
	}
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		sym_info_free(next->value);
		next->value = value;
	} else {
		newpair = hash_newpair(key, value);
		if (next == hashtable->table[index]) {
			newpair->next = next;
			hashtable->table[index] = newpair;
		} else if (next == NULL) {
			last->next = newpair;
		} else {
			newpair->next = next;
			last->next = newpair;
		}

	}
}


sym_info *hash_get(hash_t *hashtable, char *key)
{
	int index = 0;
	entry_t *pair;

	index = hash_hash(hashtable, key);

	pair = hashtable->table[index];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
		pair = pair->next;

	if(pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
		return NULL;
    else
		return pair->value;	
}

int hash_get_size(hash_t *hashtable){
	return hashtable->size;
}