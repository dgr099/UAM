/**************************************************
Nombre del modulo: p4_e3_b.c
Descripcion: Impresion de un arbol con elementos procedentes de listas
Autor:  
Fecha: 08/05/20
Modulos propios que necesita: types.h list.h stack_types.h tree.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include "types.h"
#include "list.h"
#include "stack_types.h"
#include "tree.h"


/*=== Definiciones ==========================================================*/
#define MAX_ID 1000


/*=== Funciones =============================================================*/
/*-----------------------------------------------------------------------------
Nombre: int_print_v2
Descripcion: imprime elementos con espacios entre ellos
Argumentos de entrada:
1. pf, el dispositivo en el que se desea imprimir los valores
2. ele, puntero al elemento a imprimir
Retorno:
- -1, en caso de error
- numero de caracteres impreso
-----------------------------------------------------------------------------*/
int int_print_v2(FILE *pf, const void *ele){
  if(!ele || !pf){
    return -1;
  }
  return fprintf(pf, "%d ", *(int*)ele);
}

/*-----------------------------------------------------------------------------
Nombre: listRandomAndOrdered
Descripcion: inserta n enteros aleatorios entre 0 y MAX_ID en una lista ordenada
Argumentos de entrada:
1. n, la longitud de la lista
2. pl, puntero a la lista
Retorno:
- OK, si funciona correctamente
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status listRandomAndOrdered (int n, List *pl[]){
    int i=0, *alt;
    Status st=OK;

    if (!pl[1] || !pl[2]) 
        return ERROR;

    for (i=0; i!=n && st == OK; i++) {
        alt=(int*)malloc(sizeof(int));
        (*alt) = rand ()%MAX_ID;
        st = list_pushOrder (pl[0], alt, 1);
        st=list_pushBack(pl[1], alt);
        int_free(alt);
    }

    if (st == ERROR) {
        return ERROR;
    }

    return OK;
}

/******************************************************************************/

int main (int argc, char **argv){
  List *pl[2];
  BSTree *tree[2];
  int *ele=NULL, tam, i;
  if(argc<2){
    return 1;
  }
  if(!(pl[0]=list_new(int_free, int_copy, int_print_v2, int_cmp))){
    return 1;
  }
  if(!(pl[1]=list_new(int_free, int_copy, int_print_v2, int_cmp))){
    list_free(pl[0]);
    return 1;
  }
  listRandomAndOrdered(atol(argv[1]), pl);
  fprintf(stdout, "--- Printing List: 0 ...\n");
  list_print(stdout, pl[0]);
  fprintf(stdout, "\n"); 
  if(!(tree[0]=tree_init(int_free, int_copy, int_print_v2, int_cmp))){
    list_free(pl[0]);
    list_free(pl[1]);
    return 1;
  }
  if(!(tree[1]=tree_init(int_free, int_copy, int_print_v2, int_cmp))){
    list_free(pl[0]);
    list_free(pl[1]);
    tree_destroy(tree[0]);
    return 1;
  }
  tam=list_size(pl[0]);
  for(i=0; i!=tam; i++){
    ele=list_popFront(pl[0]);
    if(tree_insert(tree[0], ele)==ERROR){
      list_free(pl[0]);
      list_free(pl[1]);
      tree_destroy(tree[0]);
      tree_destroy(tree[1]);
      int_free(ele);
      return 1;
    }
    list_pushBack(pl[0], ele);
    int_free(ele);
    ele=list_popFront(pl[1]);
    if(tree_insert(tree[1], ele)==ERROR){
      list_free(pl[0]);
      list_free(pl[1]);
      tree_destroy(tree[0]);
      tree_destroy(tree[1]);
      int_free(ele);
      return 1;
    }
    list_pushBack(pl[1], ele);
    int_free(ele);
  }
  fprintf(stdout, "Tree depth: ");
  tam=tree_depth(tree[0]);
  fprintf(stdout, "%d\n", tam);
	fprintf(stdout, "Tree postOrder Traversal ...\n");
	tree_postOrder(stdout, tree[0]);
	fprintf(stdout, "\nTree preOrder Traversal ...\n");
	tree_preOrder(stdout, tree[0]);
	fprintf(stdout, "\nTree inOrder Traversal ...\n");
	tree_inOrder(stdout, tree[0]);
	fprintf(stdout, "\n");
  fprintf(stdout, "--- Printing List: 1 ...\n");
  list_print(stdout, pl[1]);
  fprintf(stdout, "\n");
  fprintf(stdout, "Tree depth: ");
  tam=tree_depth(tree[1]);
  fprintf(stdout, "%d\n", tam);
	fprintf(stdout, "Tree postOrder Traversal ...\n");
	tree_postOrder(stdout, tree[1]);
	fprintf(stdout, "\nTree preOrder Traversal ...\n");
	tree_preOrder(stdout, tree[1]);
	fprintf(stdout, "\nTree inOrder Traversal ...\n");
	tree_inOrder(stdout, tree[1]);
	fprintf(stdout, "\n");
  list_free(pl[0]);
  list_free(pl[1]);
  tree_destroy(tree[0]);
  tree_destroy(tree[1]);
  return 0;
}
