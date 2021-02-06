/**************************************************
Nombre del módulo: Node.c
Descripción:	Funciones necesarias para trabajar con nodos
Autor:	 
Fecha:	sáb, 8 de feb de 2020
Módulos propios que necesita:	node.h
Notas:	
Modificaciones:
Mejoras pendientes:
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#define NAME_L 64

struct _Node
{
	char name[NAME_L];
	long id;
	int nConnect;
	Label label;
};
/*------------------------------
Nombre:	node_init
Descripción:	inicializacion de un nodo
Argumentos de entrada:	ninguno
Retorno:	un nodo
-------------------------------*/
Node *node_init()
{
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
/*------------------------------
Nombre:	node_free
Descripción:	liberacion de un nodo
Argumentos de entrada:	el nodo que se desea liberar
Retorno:	nada
-------------------------------*/
void node_free(void *n)
{
	if (n == NULL)
	{
		return;
	}
	free(n);
}
/*------------------------------
Nombre:	node_getId
Descripción:	obtener el id de un nodo
Argumentos de entrada:	el nodo del que se desea conocer el id
Retorno:	la id del nodo
-------------------------------*/
long node_getId(const Node *n)
{
	if (n == NULL)
	{
		return -1;
	}
	return n->id;
}
/*------------------------------
Nombre:	node_getName
Descripción:	obtener el nombre de un nodo
Argumentos de entrada:	el nodo del que se desea conocer el nombre
Retorno:	el nombre del nodo
-------------------------------*/
const char *node_getName(const Node *n)
{
	if (!n)
	{
		return NULL;
	}
	return n->name;
}
/*------------------------------
Nombre:	node_getNConnect
Descripción:	obtener el numero de conexiones de un nodo
Argumentos de entrada:	el nodo del que se desea el numero de conexiones
Retorno:	el numero de conexiones del nodo
-------------------------------*/
int node_getNConnect(const Node *n)
{
	if (!n)
	{
		return -1;
	}
	return n->nConnect;
}
/*------------------------------
Nombre:	node_getLabel
Descripción:	obtener el label del nodo
Argumentos de entrada:	el nodo del que se desea conocer el id
Retorno:	el label del nodo
-------------------------------*/
Label node_getLabel(const Node *n)
{
  if (n==NULL) {
      return -1;
  }
  return n->label;
}
/*------------------------------
Nombre: node_setLabel
Descripción:	establecer el label de un nodo
Argumentos de entrada:	el nodo al que se desea establecer un label y el label que se pretende establecer
Retorno:	Status (OK/ERROR)
-------------------------------*/
Status node_setLabel(Node *n, Label l)
{
	if (!n)
	{
		return ERROR;
	}
	n->label = l;
	return OK;
}
/*------------------------------
Nombre:	node_setId
Descripción:	establecer el Id de un nodo
Argumentos de entrada:	el nodo al que se desea establecer un id y el id correspondiente
Retorno:	Status(OK/ERROR)
-------------------------------*/
Status node_setId(Node *n, const long id)
{
	if (!n)
	{
		return ERROR;
	}
	n->id = id;
	return OK;
}
/*------------------------------
Nombre:	node_setName
Descripción:	establecer el nombre de un nodo
Argumentos de entrada:	el nodo al que se desea establecer un nombre y el nombre correspondiente
Retorno:	Status (OK/ERROR)
-------------------------------*/
Status node_setName(Node *n, const char *name)
{
	if (!n || !name)
	{
		return ERROR;
	}
	strcpy(n->name, name);
	return OK;
}
/*------------------------------
Nombre:	node_setNConnect
Descripción:	establecer el nº de conexiones de un nodo
Argumentos de entrada:	el nodo al que se desea establecer el numero de conexiones y el numero de conexiones correspondiente
Retorno:	Status (OK/ERROR)
-------------------------------*/
Status node_setNConnect(Node *n, const int cn)
{
	n->nConnect = cn;
	if (n == NULL)
	{
		return ERROR;
	}
	return OK;
}
/*------------------------------
Nombre:	node_cmp
Descripción:	comparacion de dos nodos
Argumentos de entrada:	los nodos que se desea comparar
Retorno:	devuelve un entero menor, igual o mayor que cero dependiendo de sus identificadores. Si son iguales, entonces pasa a comparar sus nombres
-------------------------------*/
int node_cmp(const void *n1, const void *n2) /*primero id y si son iguales compara los nombres*/
{
	const Node *nodo = n1, *nodo2 = n2;
	if (n1 == NULL || n2 == NULL)
	{
		return -3;
	}
	if(node_getId(nodo)==node_getId(nodo2)){
		return(strcmp(node_getName(nodo), node_getName(nodo2)));
	}
	else if (node_getId(nodo)>node_getId(nodo2)){
		return 1;
	}
	else
		return -1;
	
}
/*------------------------------
Nombre:	node_copy
Descripción:	copiar los valores de un nodo en otro nuevo
Argumentos de entrada:	el nodo que se desea replicar
Retorno:	un nuevo nodo con los valores del recivido en la entrada
-------------------------------*/
void *node_copy(const void *src)
{
	Node *nodo1;
	const Node *nodo2;
	if (src == NULL)
	{
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
/*------------------------------
Nombre:	node_print
Descripción:	imprimir los valores de un nodo
Argumentos de entrada:	el dispositivo en el que se desea imprimir los valores
Retorno:	-1 en caso de error, en caso contrario el numero de caracteres impresos por pantalla
-------------------------------*/
int node_print(FILE *pf, const void *n)
{
	const Node *nodo = n;
	if (n == NULL)
	{
		return -1;
	}
	return (fprintf(pf, "[%s, %ld, %d, %d]", nodo->name, nodo->id, nodo->label, nodo->nConnect));
}
