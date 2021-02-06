/**************************************************
Nombre del modulo: p3_e1.c
Descripcion: Manipulacion de grafos en colas
Autor:  
Fecha: 18-03-20
Modulos propios que necesita: queue_fp.h node.h graph.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_fp.h"
#include "node.h"
#include "graph.h"


/*=== Definiciones ==========================================================*/

#define MAX_SIZE 1024


/*=== Funciones =============================================================*/

int main(int argc, char **argv){
  FILE *f;
  Graph *g;
  Queue *q;
  Node *aux[MAX_SIZE], *aux2;
  int i, z;
  long *id;
  if(argc<2){
    printf("Error, debe especificar un fichero de texto");
    return 1;
  }
  if((f=fopen(argv[1], "r"))==NULL){
    return 1;
  }
  if(!(g=graph_init())){
    fclose(f);
    return 1;
  }
  if(graph_readFromFile(f, g)==ERROR){
    graph_free(g);
    fclose(f);
    return 1;
  }
  
  fclose(f);

  if(!(q=queue_init(node_free, node_copy, node_print))){
    graph_free(g);
    return 1;
  }
  z=graph_getNumberOfNodes(g);
  id=graph_getNodesId(g);
  for(i=0; i!=z; i++){
    aux2=graph_getNode(g, id[i]);
    if(queue_insert(q, aux2)==ERROR){
      graph_free(g);
      queue_free(q);
      return 1;
    }
    node_free(aux2);
  }
  free(id);
  for(i=0; i!=z; i++){
    aux[i]=queue_extract(q);
    aux2=node_copy(aux[i]);
    if(node_setLabel(aux2, BLACK)==ERROR){
      graph_free(g);
      queue_free(q);
      node_free(aux2);
      for(i=0; aux[i]!=NULL; i++){
        node_free(aux[i]);
      }
    }
    graph_setNode(g, aux2);
    node_free(aux2);
  }
  for(i=0; i!=z; i++){
    if(queue_insert(q, aux[i])==ERROR){
      graph_free(g);
      queue_free(q);
      for(i=0; aux[i]!=NULL; i++){
        node_free(aux[i]);
      }
    }
    node_free(aux[i]);
  }
  printf("Nodes in graph:\n");
  graph_print(stdout, g);
  printf("Queue size: %d\n", queue_size(q));
  printf("Nodes in queue:\n");
  queue_print(stdout, q);
  printf("\n");
  for( ; queue_isEmpty(q)!=TRUE;){
    printf("Extract Node:\n");
    aux2=queue_extract(q);
    node_print(stdout, aux2);
    node_free(aux2);
    printf("\n");
  }
  printf("Queue size: %d\n", queue_size(q));
  graph_free(g);
  queue_free(q);
  return 0;
}
