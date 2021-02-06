/**************************************************
Nombre del modulo: p3_e3_c.c
Descripcion: algoritmo busqueda en profundidad
Autor:  
Fecha: 14-04-20
Modulos propios que necesita: stack_fp.h graph.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "graph.h"


/*=== Definiciones ==========================================================*/
#define MAXSTRING 65536


/*=== Funciones =============================================================*/
/*-----------------------------------------------------------------------------
Nombre: graph_deepFirst
Descripcion: implementa el algoritmo DFS desde un nodo inicial
Argumentos de entrada:
1. pg, el puntero al grafo
2. ini_id, el id del nodo origen
3. end_id, el id del nodo destino
4. nodestraversed, cadena con el nombre de los nodos recorridos
Retorno:
- OK, si funciona
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status graph_deepFirst (Graph *pg, long ini_id, long end_id, char *nodestraversed){
  Stack *s=NULL;
  Node *node=NULL, *node2=NULL;
  int z, i;
  long *id=NULL, *e=NULL, id_aux;

  if(!pg || !nodestraversed || ini_id == -1 || end_id == -1){
    return ERROR;
  }

  if((z = graph_getNumberOfNodes(pg)) == -1){
    return ERROR;
  }

  if((id = graph_getNodesId(pg)) == NULL){
    return ERROR;
  }

  for(i=0; i!=z; i++){
    if((node = graph_getNode(pg, id[i])) == NULL){
      return ERROR;
    }
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

  if(!(s = stack_init(node_free, node_copy, node_print))){
    return ERROR;
  }

  if((node = graph_getNode(pg, ini_id)) == NULL){
    return ERROR;
  }
  if(stack_push(s, node)==ERROR){
    stack_free(s);
    node_free(node);
    return ERROR;
  }

  node_free(node);

  while(stack_isEmpty(s) != TRUE){
    if((node = stack_pop(s)) == NULL){
      return ERROR;
    }
    strcat(nodestraversed, node_getName(node));
    if(node_getId(node) == end_id){
      node_free(node);
      stack_free(s);
      return END;
    }

    if((id_aux = node_getId(node)) == -1){
      node_free(node);
      stack_free(s);
      return ERROR;
    }

    if((e = graph_getConnectionsFrom(pg, id_aux)) == NULL){
      node_free(node);
      stack_free(s);
      return ERROR;
    }

    if((z = graph_getNumberOfConnectionsFrom(pg, id_aux)) == -1){
      node_free(node);
      stack_free(s);
      free(e);
      return ERROR;
    }

    node_free(node);

    for(i=0; i!=z; i++){
        if((node2 = graph_getNode(pg, e[i])) == NULL){
          stack_free(s);
          free(e);
          return ERROR;
        }
        if(node_getLabel(node2)==WHITE){
          if(node_setLabel(node2, BLACK)==ERROR){
            stack_free(s);
            free(e);
            node_free(node2);
            return ERROR;
          }
          if(node_setPredecessorId(node2, id_aux)==ERROR){
            stack_free(s);
            free(e);
            node_free(node2);
            return ERROR;
          }
          if(stack_push(s, node2)==ERROR){
            stack_free(s);
            free(e);
            node_free(node2);
            return ERROR;            
          }
          if(graph_setNode(pg, node2)==ERROR){
            stack_free(s);
            free(e);
            node_free(node2);
            return ERROR;            
          }
        }
      node_free(node2);
    }
    free(e);
    strcat(nodestraversed, " ");
  }
  stack_free(s);
  return OK;
}


int main(int argc, char **argv){
  Graph *g=NULL;
  char *name=NULL;
  Status st;
  FILE *f=NULL;

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
  st=graph_deepFirst(g, (int)*argv[2]-'0', (int)*argv[3]-'0', name);
  printf("%s\n", name);
  graph_free(g);
  free(name);
  fclose(f);
  return 0;
}
