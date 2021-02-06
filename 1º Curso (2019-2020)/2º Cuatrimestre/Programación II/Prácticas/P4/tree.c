/**************************************************
Nombre del modulo: tree.c
Descripcion: Funciones para el manejo de arboles
Autor:  
Fecha: 06/05/20
Modulos propios que necesita: types.h tree.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tree.h"


/*=== Definiciones ==========================================================*/
typedef struct _BTNode {
	void *info;
	struct _BTNode *left;
	struct _BTNode *right;
} BTNode;

struct _BSTree {
	BTNode *root;

	destroy_element_function_type		destroy_element;
	copy_element_function_type 			copy_element;
	print_element_function_type 		print_element;
	cmp_element_function_type 			cmp_element;
};


/*=== Funciones =============================================================*/
/*** DECLARACIÓN DE FUNCIONES PRIVADAS ***/

/* Crea un BTNodo */
BTNode* bt_node_new();
/* Libera un BTNodo */
void bt_node_free (BTNode *pn, destroy_element_function_type free_elem);

/* Recursiva para destruir un arbol */
void tree_destroyRec(BTNode *node, BSTree *t);

/* Recursive para hallar la profundidad de un arbol */
int tree_depthRec(const BTNode *node);

/* Recursive para insertar un elemento en un arbol */
BTNode *tree_insertRec(BTNode *node, const void *elem, BSTree *t);

/* Recursive para recorrido preorden */
void tree_preOrderRec(FILE *f, BTNode *node, const BSTree *t);
/* Recursive para recorrido inorden */
void tree_inOrderRec(FILE *f, BTNode *node, const BSTree *t);
/* Recursive para recorrido postorden */
void tree_postOrderRec(FILE *f, BTNode *node, const BSTree *t);


/*** PRIMITIVAS PRIVADAS DE BT-NODOS ***/
BTNode * bt_node_new(){
	BTNode* pn = NULL;

	pn = (BTNode*)malloc(sizeof(BTNode));
	if (!pn) {
		fprintf (stderr,"%s\n", strerror (errno));
		return NULL;
	}

	pn->left = pn->right = NULL;
	pn->info = NULL;
	return pn;
}

void bt_node_free (BTNode *pn, destroy_element_function_type free_elem){
	if (!pn) return;
	free_elem(pn->info);
	free(pn);
}


/*** CREACIÓN Y LIBERACIÓN DE UN ÁRBOL ***/
/*Inicializa un árbol vacío.*/
BSTree* tree_init(destroy_element_function_type f1,
copy_element_function_type f2,
print_element_function_type f3,
cmp_element_function_type f4){

	BSTree* tree = malloc (sizeof(BSTree));
	if (!tree){
		fprintf (stderr,"%s\n", strerror (errno));
	return NULL;
	}

	tree->root = NULL;
	
	tree->destroy_element=f1;
	tree->copy_element=f2;
	tree->print_element=f3;
	tree->cmp_element=f4;
	return tree;
}


/*Indica si el árbol está o no vacio*/
Bool tree_isEmpty(const BSTree *tree){
	if(!tree){
		return TRUE;
	}

	if(!tree->root){
		return TRUE;
	}

	return FALSE;
}


/*Libera la memoria utilizada por un árbol.*/
void tree_destroy(BSTree *tree){
	if(!tree){
		return;
	}

	tree_destroyRec(tree->root, tree);

	free(tree);
}

void tree_destroyRec(BTNode *node, BSTree *t){
	if(!node){
		return;
	}

	tree_destroyRec(node->left, t);
	tree_destroyRec(node->right, t);
	bt_node_free(node, t->destroy_element);
}


/*Indica la profundidad del árbol. Un árbol vacio profundidad -1*/
int tree_depth (const BSTree *tree){
	if(!tree){
		return -1;
	}

	if(tree_isEmpty(tree) == TRUE){
		return -1;
	}

	return tree_depthRec(tree->root);
}

int tree_depthRec(const BTNode *node){
	int left=0, right=0;

	if(!node){
		return -1;
	}

	left = tree_depthRec(node->left);
	right = tree_depthRec(node->right);

	if(left > right){
		return 1 + left;
	}
	else{
		return 1 + right;
	}
}


/*** INSERCIÓN ***/
/*Inserta un elemento en un árbol binario de búsqueda.*/
Status tree_insert (BSTree *tree, const void *elem){
	BTNode *node = NULL;

	if(!tree || !elem){
		return ERROR;
	}

	if(!(node = tree_insertRec(tree->root, elem, tree))){
		return ERROR;
	}
	tree->root = node;

	return OK;
}

BTNode *tree_insertRec(BTNode *node, const void *elem, BSTree *t){
	int cmp;
	Node* copy=NULL;;

	if(!elem){
		return NULL;
	}

	if(node == NULL){
		if(!(node = bt_node_new())){
			return NULL;
		}
		copy=t->copy_element(elem);
		if((node->info = copy) == NULL){
			free(node);
			return NULL;
		}
		return node;
	}

	cmp = t->cmp_element(elem, node->info);
	if(cmp < 0){
		node->left = tree_insertRec(node->left, elem, t);
	}
	else if(cmp > 0){
		node->right = tree_insertRec(node->right, elem, t);
	}
	return node;
}


/*** RECORRIDOS ***/
/*Recorre un árbol en orden previo.*/
void tree_preOrder (FILE *f, const BSTree *tree){
	if(!f){
		return;
	}

	if(tree_isEmpty(tree) == TRUE){
		return;
	}

	tree_preOrderRec(f, tree->root, tree);
}

void tree_preOrderRec(FILE *f, BTNode *node, const BSTree *t){
	if(!f || !node){
		return;
	}

	if((t->print_element(f, node->info)) == -1){
		return;
	}
	tree_preOrderRec(f, node->left, t);
	tree_preOrderRec(f, node->right, t);
}


/*Recorre un árbol en orden medio.*/
void tree_inOrder (FILE *f, const BSTree *tree){
	if(!f){
		return;
	}

	if(tree_isEmpty(tree) == TRUE){
		return;
	}

	tree_inOrderRec(f, tree->root, tree);
}

void tree_inOrderRec(FILE *f, BTNode *node, const BSTree *t){
	if(!f || !node){
		return;
	}
	tree_inOrderRec(f, node->left, t);
	if(t->print_element(f, node->info) == -1){
		return;
	}
	tree_inOrderRec(f, node->right, t);
}


/*Recorre un árbol en orden posterior.*/
void tree_postOrder(FILE *f, const BSTree *tree){
	if(!f){
		return;
	}

	if(tree_isEmpty(tree) == TRUE){
		return;
	}

	tree_postOrderRec(f, tree->root, tree);
}

void tree_postOrderRec(FILE *f, BTNode *node, const BSTree *t){
	if(!f || !node){
		return;
	}

	tree_postOrderRec(f, node->left, t);
	tree_postOrderRec(f, node->right, t);
	if((t->print_element(f, node->info)) == -1){
		return;
	}
}
