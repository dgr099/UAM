/**************************************************
Nombre del modulo: p4_e2_option1.c
Descripcion: Algoritmo BFS con grafos que usan listas para las conexiones
Autor:  
Fecha: 23-03-20
Modulos propios que necesita: types.h graph.h queue_fp.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "graph_option2.h"
#include "queue_fp.h"


/*=== Definiciones ==========================================================*/

#define MAXSTRING 65536


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: graph_breadthFirst
Descripcion: implementa el algoritmo BFS desde un nodo inicial
Argumentos de entrada:
1. pg, el puntero al grafo
2. ini_id, el id del nodo origen
3. end_id, el id del nodo destino
4. nodestraversed, cadena con el nombre de los nodos recorridos
Retorno:
- OK, si funciona
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status graph_breadthFirst (Graph *pg, long ini_id, long end_id, char *nodestraversed){
  Queue* q;
  Node* node;
  int z, i;
  long *id=NULL, *e=NULL;
  if(!pg || !nodestraversed || ini_id == -1 || end_id == -1){
    return ERROR;
  }
  z=graph_getNumberOfNodes(pg);
  id=graph_getNodesId(pg);
  for(i=0; i!=z; i++){
    node=graph_getNode(pg, id[i]);
    if(node_getId(node)==ini_id){
      if(node_setLabel(node, BLACK)==ERROR){
        node_free(node);
        free(id);
        return ERROR;
      }
    }
    else{
      if(node_setLabel(node, WHITE)==ERROR){
        node_free(node);
        free(id);
        return ERROR;        
      }
    }
    if(graph_setNode(pg, node)==ERROR){
        node_free(node);
        free(id);
        return ERROR;         
    }
    node_free(node);
  }
  free(id);

  if(!(q=queue_init(node_free, node_copy, node_print))){
    return ERROR;
  }
  node=graph_getNode(pg, ini_id);
  if(queue_insert(q, node)==ERROR){
    queue_free(q);
    node_free(node);
    return ERROR;
  }
  node_free(node);
  while(queue_isEmpty(q)!=TRUE){
    node=queue_extract(q);
    strcat(nodestraversed, node_getName(node));
    if(node_getId(node)==end_id){
      node_free(node);
      queue_free(q);
      return END;
    }
    e=graph_getConnectionsFrom(pg, node_getId(node));
    z=graph_getNumberOfConnectionsFrom(pg, node_getId(node));
    node_free(node);
    for(i=0; i!=z; i++){
        node=graph_getNode(pg, e[i]);
        if(node_getLabel(node)==WHITE){
          if(node_setLabel(node, BLACK)==ERROR){
            queue_free(q);
            free(e);
            node_free(node);
            return ERROR;
          }
          if(queue_insert(q, node)==ERROR){
            queue_free(q);
            free(e);
            node_free(node);
            return ERROR;            
          }
          if(graph_setNode(pg, node)==ERROR){
            queue_free(q);
            free(e);
            node_free(node);
            return ERROR;            
          }
        }
      node_free(node);
    }
    free(e);
    strcat(nodestraversed, " ");
  }
  queue_free(q);
  return OK;
}


int main(int argc, char **argv){
  Graph *g=NULL;
  char *name=NULL;
  Status st;
  FILE *f=NULL;
  int a;
  int b;
  if(argc<4){
    return 1;
  }
  if(!(f=fopen(argv[1], "r"))){
    return 1;
  }
  if(!(g=graph_init())){
    return 1;
  }
  if(graph_readFromFile(f, g)==ERROR){
    return 1;
  }
  if(!(name=calloc(MAXSTRING, sizeof(char)))){
    return 1;
  }
  a=atol(argv[2]);
  b=atol(argv[3]);
  st=graph_breadthFirst(g, a, b, name);
  if(st==ERROR){
    return 1;
  }
  
  printf("%s\n", name);
  graph_free(g);
  free(name);
  fclose(f);
  return 0;
}
