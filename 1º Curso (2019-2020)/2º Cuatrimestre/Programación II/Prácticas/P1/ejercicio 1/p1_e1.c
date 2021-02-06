/**************************************************
Nombre del módulo:	p1_e1.c
Descripción:	
Autor:	 
Fecha:	mar, 4 de feb, 2020
Módulos propios que necesita:	node.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/
#include <stdio.h>
#include "node.h"
int main()
{
	Node *nodo1, *nodo2;
	Status cod;
	int cod2;
	nodo1 = node_init();
	nodo2 = node_init();
	if(nodo2==NULL){
		node_free(nodo1);
	}
	cod = node_setName(nodo1, "first");
	if (cod == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	if ((cod = node_setName(nodo2, "second")) == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod = node_setId(nodo1, 111);
	if (cod == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod = node_setId(nodo2, 222);
	if (cod == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod = node_setLabel(nodo1, WHITE);
	if (cod == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod = node_setLabel(nodo2, WHITE);
	if (cod == ERROR)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod2 = node_print(stdout, nodo1);
	if (cod2 == -1)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod2 = node_print(stdout, nodo2);
	if (cod2 == -1)
	{
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	printf("\nSon iguales? ");
	cod2 = node_cmp(nodo1, nodo2);
	if(cod2==0){
		printf("Sí\n");
	}
	else
		printf("No\n");
	printf("Id del primer nodo: %ld\n", node_getId(nodo1));
	printf("Nombre del segundo nodo es: %s\n", node_getName(nodo2));
	node_free(nodo2);
	nodo2 = node_copy(nodo1);
	if(nodo2==NULL){
		printf("Error en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod2 = node_print(stdout, nodo1);
	if (cod2 == -1)
	{
		printf("\nError en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	cod2 = node_print(stdout, nodo2);
	if (cod2 == -1)
	{
		printf("\nError en la ejecución del programa\n");
		node_free(nodo1);
		node_free(nodo2);
		return 1;
	}
	printf("\nSon iguales? ");
	cod2 = node_cmp(nodo1, nodo2);
	if(cod2==0){
		printf("Sí\n");
	}
	else
		printf("No\n");
	node_free(nodo1);
	node_free(nodo2);
	return 0;
}
