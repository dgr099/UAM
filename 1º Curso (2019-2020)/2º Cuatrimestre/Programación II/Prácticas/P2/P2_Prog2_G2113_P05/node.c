/**************************************************
Nombre del modulo: node.c
Descripcion: Funciones necesarias para trabajar con nodos
Autor:	 
Fecha: 08-02-20
Modulos propios que necesita: node.h
Notas:	
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


/*=== Definiciones ==========================================================*/

#define NAME_L 64

struct _Node
{
	char name[NAME_L];
	long id;
	int nConnect;
	Label label;
};


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: node_init
Descripcion: Inicializa un nodo
Argumentos de entrada: Ninguno
Retorno:
- n, un puntero a nodo
- NULL, si falla
-----------------------------------------------------------------------------*/
Node *node_init(){
	Node *n;

	n = (Node *)calloc(1, sizeof(Node));
	if (n == NULL)
		return NULL;

	n->name[0] = '\0';
	n->id = -1;
	n->nConnect = 0;
	n->label = WHITE;

	if (n == NULL)
		return NULL;
	else
		return n;
}

/*-----------------------------------------------------------------------------
Nombre: node_free
Descripcion: Libera un nodo
Argumentos de entrada:
1. n, el nodo que se desea liberar
Retorno: Nada
-----------------------------------------------------------------------------*/
void node_free(void *n){
	if (n == NULL){
		return;
	}
	free(n);
}

/*-----------------------------------------------------------------------------
Nombre: node_getId
Descripcion: Obtiene el id de un nodo
Argumentos de entrada:
1. n, el nodo del que se desea conocer el id
Retorno:
- id, la id del nodo
- -1 en caso de error
-----------------------------------------------------------------------------*/
long node_getId(const Node *n){
	if (n == NULL){
		return -1;
	}
	return n->id;
}

/*-----------------------------------------------------------------------------
Nombre: node_getName
Descripcion: Obtiene el nombre de un nodo
Argumentos de entrada:
1. n, el nodo del que se desea conocer el nombre
Retorno:
- name, el nombre del nodo
- NULL, si falla
-----------------------------------------------------------------------------*/
const char *node_getName(const Node *n){
	if (!n){
		return NULL;
	}
	return n->name;
}

/*-----------------------------------------------------------------------------
Nombre: node_getNConnect
Descripcion: Obtiene el numero de conexiones de un nodo
Argumentos de entrada:
1. n, el nodo del que se desea el numero de conexiones
Retorno:
- nConnect, el numero de conexiones del nodo
- -1 en caso de error
-----------------------------------------------------------------------------*/
int node_getNConnect(const Node *n){
	if (!n){
		return -1;
	}
	return n->nConnect;
}

/*-----------------------------------------------------------------------------
Nombre: node_getLabel
Descripcion: Obtiene el label de un nodo
Argumentos de entrada:
1. n, el nodo del que se desea conocer el label
Retorno:
- label, el label del nodo
- -1 en caso de error
-----------------------------------------------------------------------------*/
Label node_getLabel(const Node *n){
  if (n==NULL){
      return ERROR_NODE;
  }
  return n->label;
}

/*-----------------------------------------------------------------------------
Nombre: node_setLabel
Descripcion: Establece el label de un nodo
Argumentos de entrada:
1. n, el nodo al que se desea establecer un label
2. l, el label que se pretende establecer
Retorno:
- OK, si se ha terminado sin problemas
- ERROR en caso contrario
-----------------------------------------------------------------------------*/
Status node_setLabel(Node *n, Label l){
	if (!n){
		return ERROR;
	}
	n->label = l;
	return OK;
}

/*-----------------------------------------------------------------------------
Nombre: node_setId
Descripcion: Establece el id de un nodo
Argumentos de entrada:
1. n, el nodo al que se desea establecer un id
2. id, el id a establecer
Retorno:
- OK, si se ha terminado sin problemas
- ERROR en caso contrario
-----------------------------------------------------------------------------*/
Status node_setId(Node *n, const long id){
	if (!n){
		return ERROR;
	}
	n->id = id;
	return OK;
}

/*-----------------------------------------------------------------------------
Nombre: node_setName
Descripcion: Establece el nombre de un nodo
Argumentos de entrada:
1. n, el nodo al que se desea establecer un nombre
2. name, el nombre a establecer
Retorno:
- OK, si se ha terminado sin problemas
- ERROR en caso contrario
-----------------------------------------------------------------------------*/
Status node_setName(Node *n, const char *name){
	if (!n || !name){
		return ERROR;
	}
	strcpy(n->name, name);
	return OK;
}

/*-----------------------------------------------------------------------------
Nombre: node_setNConnect
Descripcion: Establece el numero de conexiones de un nodo
Argumentos de entrada:
1. n, l nodo al que se desea establecer el numero de conexiones
2. cn, el numero de conexiones correspondiente
Retorno:
- OK, si se ha terminado sin problemas
- ERROR en caso contrario
-----------------------------------------------------------------------------*/
Status node_setNConnect(Node *n, const int cn){
	n->nConnect = cn;
	if (n == NULL){
		return ERROR;
	}
	return OK;
}

/*-----------------------------------------------------------------------------
Nombre: node_cmp
Descripcion: Compara dos nodos
Argumentos de entrada:
1. n1, el primer nodo a comparar
2. n2, el segundo nodo a comparar
Retorno:
- -3 si falla
- el resultado de comparar los nombres
- -1 si el id del primer nodo es mayor que el del segundo
- -1 en caso contrario
-----------------------------------------------------------------------------*/
int node_cmp(const void *n1, const void *n2){
	const Node *nodo = n1, *nodo2 = n2;
	if (n1 == NULL || n2 == NULL){
		return -3;
	}
	/* primero compara id y si son iguales compara los nombres */
	if(node_getId(nodo)==node_getId(nodo2)){
		return(strcmp(node_getName(nodo), node_getName(nodo2)));
	}
	else if (node_getId(nodo)>node_getId(nodo2)){
		return 1;
	}
	else
		return -1;
	
}

/*-----------------------------------------------------------------------------
Nombre: node_copy
Descripcion: Copia los valores de un nodo en otro nuevo
Argumentos de entrada:
1. src, el nodo que se desea replicar
Retorno:
- NULL, si falla
- nodo1, el nodo resultante tras la copia
-----------------------------------------------------------------------------*/
void *node_copy(const void *src){
	Node *nodo1;
	const Node *nodo2;
	if (src == NULL){
		return NULL;
	}
	nodo2 = src;
	nodo1 = node_init();
	nodo1->id = nodo2->id;
	nodo1->nConnect = nodo2->nConnect;
	nodo1->label = nodo2->label;
	strcpy(nodo1->name, nodo2->name);
	return nodo1;
}

/*-----------------------------------------------------------------------------
Nombre: node_print
Descripcion: Imprime los valores de un nodo
Argumentos de entrada:
1. pf, el puntero al dispositivo donde se va a imprimir
2. n, el que posteriormente sera un puntero a nodo
Retorno:
- -1, si falla
- el numero de caracteres impresos por pantalla
-----------------------------------------------------------------------------*/
int node_print(FILE *pf, const void *n){
	const Node *nodo = n;
	if ( !n || !pf){
		return -1;
	}
	return (fprintf(pf, "[%s, %ld, %d, %d]", nodo->name, nodo->id, nodo->label, nodo->nConnect));
}
