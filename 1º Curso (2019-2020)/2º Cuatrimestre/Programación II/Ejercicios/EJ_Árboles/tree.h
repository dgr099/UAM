#ifndef TREE_H
#define TREE_H

#include "types.h"

typedef struct _BSTree BSTree;

/* Tipos de los punteros a función soportados por el árbol */
typedef void (*destroy_element_function_type)(void *);
typedef void *(*copy_element_function_type)(const void *);
typedef int (*print_element_function_type)(FILE *, const void *);
/* Esta función devuelve un entero menor, igual o mayor que 0 según si el primer
 * argumento es menor, igual o mayor que el segundo argumento */
typedef int (*cmp_element_function_type)(const void *, const void *);

typedef struct _BTNode {
  void *info;
  struct _BTNode *left;
  struct _BTNode *right;
} BTNode;

struct _BSTree {
  BTNode *root;

  destroy_element_function_type destroy_element;
  copy_element_function_type copy_element;
  print_element_function_type print_element;
  cmp_element_function_type cmp_element;
};

BSTree *
tree_init(destroy_element_function_type f1, copy_element_function_type f2,
          print_element_function_type f3,
          cmp_element_function_type f4); /* Inicializa un árbol vacío. */

void tree_destroy(BSTree *tree); /* Libera la memoria utilizada por un árbol. */

Status tree_insert(BSTree *tree,
                   const void *elem); /* Inserta un elemento en un árbol binario
                                         de búsqueda. */
Status tree_delete(
    BSTree *tree,
    const void *elem); /* Borra un elemento de un árbol binario de búsqueda. */

Bool tree_search(
    BSTree *tree,
    const void *elem); /* Busca un elemento en un árbol binario de búsqueda. */

void tree_preOrder(FILE *f,
                   const BSTree *tree); /* Recorre un árbol en orden previo. */
void tree_inOrder(FILE *f,
                  const BSTree *tree); /* Recorre un árbol en orden medio. */
void tree_postOrder(
    FILE *f, const BSTree *tree); /* Recorre un árbol en orden posterior. */

int tree_depth(const BSTree *tree); /* Calcula la profundidad de un árbol. Un
                                       árbol vacío tiene profundidad -1. */
int tree_numNodes(
    const BSTree *tree); /* Calcula el número de nodos de un árbol. Un árbol
                            vacío tiene 0 nodos. */
Bool tree_isEmpty(const BSTree *tree); /* Indica si el árbol está o no vacío. */

/* Inserta un elemento en un árbol binario de búsqueda; implementación
 * alternativa*/
Status tree_insert_alt(BSTree *tree, const void *elem);

/* Funciones adicionales */
BSTree *tree_copy(BSTree *tree);
void bt_mirrorTree(BSTree *tree);

#endif // TREE_H
