/**************************************************
Nombre del módulo:	p1_e2.c
Descripción:	
Autor:	 
Fecha:	vie, 14 de feb de 2020
Módulos propios que necesita:	graph.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/

#include <stdio.h>
#include "graph.h"

int main() {
/*Inicializa dos nodos. El primero con nombre “first”, id 111 y label WHITE y el segundo con nombre “second”, id 222 y label WHITE)*/
	Node *nodo1, *nodo2;
	Graph *g;
	nodo1 = node_init();
	if(nodo1==NULL){
		printf("Error en la ejecución del programa\n");
		return 1;
	}
	nodo2 = node_init();
	if(nodo2==NULL){
		node_free(nodo1);
		printf("Error en la ejecución del programa\n");
		return 1;
	}
	/*node_setName devuelve STATUS*/
	if (node_setName(nodo1, "first") == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);		
		return 1;
	}
	if (node_setName(nodo2, "second") == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	/*node_setId devuelve STATUS*/
	if (node_setId(nodo1, 111) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	if (node_setId(nodo2, 222) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);	
		return 1;
	}
	/*node_setLabel devuelve STATUS*/
	if (node_setLabel(nodo1, WHITE) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	if (node_setLabel(nodo2, WHITE) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
/*Inicialice un grafo.*/
	if ((g=graph_init())==NULL)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);	
		return 1;
	}
/*Insertar el nodo 1 y verifique si la inserción se realizó correctamente*/
	if (graph_insertNode (g, nodo1) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		graph_free(g);	
		return 1;
	}
	else	
		printf("Insertando nodo 1...resultado...: 1\n");

/*Insertar el nodo 2 y verifique si la inserción se realizó correctamente*/
	if (graph_insertNode (g, nodo2) == ERROR)
	{
		printf("Error en la ejecución del programa");
		return 1;
	}
	else	
		printf("Insertando nodo 2...resultado...: 1\n");

/*Insertar una conexión entre el nodo 2 y el nodo 1*/
	if (graph_insertEdge (g, node_getId(nodo2), node_getId(nodo1)) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		graph_free(g);	
		return 1;
	}
	else
		printf("Insertando edge: nodo 2 ---> nodo 1\n");

/*Comprobar si el nodo 1 está conectado con el nodo 2 (ver mensaje más abajo)*/
	if (graph_areConnected (g, node_getId(nodo1), node_getId(nodo2)) == FALSE)
	{
		printf("Conectados nodo 1 y nodo 2? No\n");
	}
	else
		printf("Conectados nodo 1 y nodo 2? Si\n");
	/*Comprobar si el nodo 2 está conectado con el nodo 1 (ver mensaje más abajo)*/
	if (graph_areConnected (g, node_getId(nodo2), node_getId(nodo1)) == FALSE)
	{
		printf("Conectados nodo 2 y nodo 1? No\n");
	}
	else
		printf("Conectados nodo 2 y nodo 1? Si\n");
	if (graph_insertNode(g, nodo2) == ERROR)
	{
		printf("Insertando nodo 2....resultado: 0\n");
	}
	else
		printf("Insertando nodo 2....resultado: 1\n");
	graph_print(stdout, g);
	node_free(nodo1);
	node_free(nodo2);
	graph_free(g);
	return 0;
}




