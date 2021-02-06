/**************************************************
Nombre del módulo:	p1_e3.c
Descripción:	
Autor:	 
Fecha:	mié, 19 de feb de 2020
Módulos propios que necesita:	graph.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/

#include <stdio.h>
#include "graph.h"

int main(int argc, char* argv[]){
	FILE *f;
	Status cod;
	Graph *g;
	if(argc<2){
		printf("Error, utilice ./nombre_ejecutable nombre_fichero para el correcto funcionamiento\n");
		return 1;
	}
	g=graph_init();
	if(g==NULL){
		return 1;
	}
	if((f=fopen(argv[1], "r"))==NULL){
		graph_free(g);
		return 1;
	}
	cod=graph_readFromFile(f, g);
	if(cod==ERROR){
		graph_free(g);
		fclose(f);
		return 1;
	}
	graph_print(stdout, g);
	graph_free(g);
	fclose(f);
	return 0;
}





