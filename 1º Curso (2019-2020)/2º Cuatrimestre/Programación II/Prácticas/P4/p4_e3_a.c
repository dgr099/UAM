/**************************************************
Nombre del modulo: p4_e3_a.c
Descripcion: Distintas formas de recorrer un arbol
Autor:  
Fecha: 08/05/20
Modulos propios que necesita: tree.h graph.h node.h types.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "graph.h"


/*=== Funciones =============================================================*/
int main(int argc, char **argv){
	Graph *g = NULL;
	FILE *f = NULL;
	BSTree *tree = NULL;
	Node *naux = NULL;
	int num, i;
	long *array;
	
	if(argc<2){
		printf("Error, utilice ./nombre_ejecutable nombre_fichero para el correcto funcionamiento");
		return 1;
	}
	
	if(!(f = fopen(argv[1], "r"))){
  		return 1;
  	}

	if(!(g = graph_init())){
    	fclose(f);
    	return 1;
  	}

	if((graph_readFromFile(f, g)) == ERROR){
		fclose(f);
		graph_free(g);
		return 1;
	}
	fclose(f);

	fprintf(stdout, "Printing graph...\n");
	if((graph_print(stdout, g)) == -1){
		graph_free(g);
		return 1;
	}
	if((num = graph_getNumberOfNodes(g)) == -1){
		graph_free(g);
    	return 1;
	}
	if(!(array = graph_getNodesId(g))){
		graph_free(g);
    	return 1;
	}
	if(!(tree = tree_init(node_free, node_copy, node_print, node_cmp))){
		graph_free(g);
		free(array);
		return 1;
	}
	for(i=num-1; i!=-1; i--){
		if(!(naux = graph_getNode(g, array[i]))){
			graph_free(g);
			free(array);
			tree_destroy(tree);
			return 1;
		}
		if((tree_insert(tree, naux)) == ERROR){
			graph_free(g);
			free(array);
			tree_destroy(tree);
			return 1;
		}
		node_free(naux);
	}

	fprintf(stdout, "Tree postOrder Traversal ...\n");
	tree_postOrder(stdout, tree);
	fprintf(stdout, "\nTree preOrder Traversal ...\n");
	tree_preOrder(stdout, tree);
	fprintf(stdout, "\nTree inOrder Traversal ...\n");
	tree_inOrder(stdout, tree);
	fprintf(stdout, "\n");
	graph_free(g);
	free(array);
	tree_destroy(tree);
	return 0;
}
