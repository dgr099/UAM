/**************************************************
Nombre del modulo: p3_e3.c
Descripcion: funciones pathToFrom y pathFromTo
Autor:  
Fecha: 14-04-20
Modulos propios que necesita: queue_fp.h graph.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"


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
  Queue *q = NULL;
  Node *node = NULL, *node2 = NULL;
  int z, i;
  long *id = NULL, *e = NULL, id_aux;

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

  if(!(q = queue_init(node_free, node_copy, node_print))){
    return ERROR;
  }

  if((node = graph_getNode(pg, ini_id)) == NULL){
    return ERROR;
  }
  if(queue_insert(q, node)==ERROR){
    queue_free(q);
    node_free(node);
    return ERROR;
  }

  node_free(node);

  while(queue_isEmpty(q) != TRUE){
    if((node = queue_extract(q)) == NULL){
      return ERROR;
    }
    strcat(nodestraversed, node_getName(node));
    if(node_getId(node) == end_id){
      node_free(node);
      queue_free(q);
      return END;
    }

    if((id_aux = node_getId(node)) == -1){
      node_free(node);
      queue_free(q);
      return ERROR;
    }

    if((e = graph_getConnectionsFrom(pg, id_aux)) == NULL){
      node_free(node);
      queue_free(q);
      return ERROR;
    }

    if((z = graph_getNumberOfConnectionsFrom(pg, id_aux)) == -1){
      node_free(node);
      queue_free(q);
      free(e);
      return ERROR;
    }

    node_free(node);

    for(i=0; i!=z; i++){
        if((node2 = graph_getNode(pg, e[i])) == NULL){
          queue_free(q);
          free(e);
          return ERROR;
        }
        if(node_getLabel(node2)==WHITE){
          if(node_setLabel(node2, BLACK)==ERROR){
            queue_free(q);
            free(e);
            node_free(node2);
            return ERROR;
          }
          if(node_setPredecessorId(node2, id_aux)==ERROR){
            queue_free(q);
            free(e);
            node_free(node2);
            return ERROR;
          }
          if(queue_insert(q, node2)==ERROR){
            queue_free(q);
            free(e);
            node_free(node2);
            return ERROR;            
          }
          if(graph_setNode(pg, node2)==ERROR){
            queue_free(q);
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
  queue_free(q);
  return OK;
}


/*-----------------------------------------------------------------------------
Nombre: pathFromTo_rec
Descripcion: imprime un camino desde el nodo origen al destino usando predecesores
Argumentos de entrada:
1. dev, puntero al dispositivo donde se va a imprimir
2. g, puntero al grafo
3. orignid, id del nodo de origen
4. actualid, id del nodo actual
Retorno:
- c, el numero de caracteres impreso
- -1 en caso de error
-----------------------------------------------------------------------------*/
int pathFromTo_rec(FILE *dev, Graph *g, long originid, long actualid){
	int c = 0;
	long predid;
	Node *node = NULL;

	if(!dev || !g){
		return -1;
	}

	/*como se va a utilizar la funcion node_print en vez de
	* printNode, es necesario obtener el nodo antes, para
	* enviarlo como parametro*/

	/*get actual node*/
	node = graph_getNode(g, actualid);
	if(!node){
		return -1;
	}

	/*base case*/
	if(originid == actualid){
		if((c = node_print(dev, node)) == -1){
			node_free(node);
			return -1;
		}
    node_free(node);
		return c;
	}

	/*get predecessor id*/
	predid = node_getPredecessorId(node);
	if(predid == -1){
		node_free(node);
		return -1;
	}

	/*recursive call*/
	c = pathFromTo_rec(dev, g, originid, predid);
	if(c == -1){
		node_free(node);
		return -1;
	}

	/*print actual node*/
	c += node_print(dev, node);

	node_free(node);
	
	return c;
}


/*-----------------------------------------------------------------------------
Nombre: pathToFrom
Descripcion: imprime un camino desde el nodo destino al origen usando predecesores
Argumentos de entrada:
1. dev, puntero al dispositivo donde se va a imprimir
2. g, puntero al grafo
3. orignid, id del nodo de origen
4. toid, id del nodo destino
Retorno:
- num, el numero de caracteres impreso
- -1 en caso de error
-----------------------------------------------------------------------------*/
int pathToFrom (FILE *dev, Graph *g, long orignid, long toid){
	if(!dev || !g){
		return -1;
	}
	return pathFromTo_rec(dev, g, toid, orignid);
}


/*-----------------------------------------------------------------------------
Nombre: pathFromTo
Descripcion: imprime un camino desde el nodo origen al destino usando predecesores
Argumentos de entrada:
1. dev, puntero al dispositivo donde se va a imprimir
2. g, puntero al grafo
3. orignid, id del nodo de origen
4. toid, id del nodo destino
Retorno:
- num, el numero de caracteres impreso
- -1 en caso de error
-----------------------------------------------------------------------------*/
int pathFromTo (FILE *dev, Graph *g, long orignid, long toid){
	if (!dev || !g){
		return -1;
	}

	return pathFromTo_rec(dev, g, orignid, toid);
}


int main (int argc, char**argv){
	FILE *f = NULL;
	Graph *g = NULL;
	long or_id, des_id;
	char names[MAXSTRING] = "";

	if(argc<4){
		return 1;
	}

	if(!(f=fopen(argv[1], "r"))){
    return 1;
  }

	if(!(g=graph_init())){
    return 1;
  }

	if(graph_readFromFile(f, g) == ERROR){
		graph_free(g);
		fclose(f);
		return 1;
	}

	or_id = atol(argv[2]);
	des_id = atol(argv[3]);

	if(graph_breadthFirst(g, or_id, des_id, names) != END){
		graph_free(g);
		fclose(f);
		return 1;
	}

	fprintf(stdout, " From Origin to End:\n");
	if(pathFromTo(stdout, g, or_id, des_id) == -1){
		graph_free(g);
		fclose(f);
		return 1;
	}

	if(graph_breadthFirst(g, des_id, or_id, names) != END){
		graph_free(g);
		fclose(f);
		return 1;
	}

	fprintf(stdout, "\n From End to Origin:\n");
	if(pathToFrom(stdout, g, or_id, des_id) == -1){
		graph_free(g);
		fclose(f);
		return 1;
	}

	graph_free(g);
	fclose(f);
	
	return 0;
}
