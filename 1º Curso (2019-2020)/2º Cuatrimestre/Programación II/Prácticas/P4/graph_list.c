/**************************************************
Nombre del modulo: graph_list.c
Descripcion: TAD graph implementado con listas
Autor:  
Fecha: 07-05-20
Modulos propios que necesita: list.h node.h graph_list.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include "node.h"
#include "graph_list.h"


/*=== Definiciones ==========================================================*/
#define MAX_NODES 1064

struct _Graph {
List *plnode; /*!<List with the graph nodes */
Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
int num_nodes; /*!<Total number of nodes in the graph */
int num_edges; /*!<Total number of connections in the graph */
};


/*=== Funciones =============================================================*/
/*-----------------------------------------------------------------------------
Nombre: find_node_index
Descripcion: devuelve el indice de un nodo
Argumentos de entrada:
1. g, el puntero al grafo
2. nId1, el id del nodo
Retorno:
- i, el indice del nodo
- -1, en caso de error
-----------------------------------------------------------------------------*/
int find_node_index (const Graph * g, int nId1) {
  int i;
  if (!g) return -1;
  for(i=0; i!=g->num_nodes; i++){
    if(node_getId(list_getElementInPos(g->plnode, i))==nId1)
      return i;
  }
  /* ID not found*/
  return -1;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getConnectionsIndex
Descripcion: devuelve un array con los indices de los nodos conectados
Argumentos de entrada:
1. g, el puntero al grafo
2. index, el indice del nodo
Retorno:
- NULL, en caso de error
- array, el array con los indices
-----------------------------------------------------------------------------*/
int* graph_getConnectionsIndex(const Graph *g, int index){
  int *array=NULL, i, j, size, index_aux;
  if(!g || index<0 || index>=g->num_nodes)
    return NULL;
  index_aux=g->num_nodes-index-1;
  size=node_getNConnect(list_getElementInPos(g->plnode, index));
  array = (int *) malloc(sizeof (int) * size);
  if (!array) {
  /* print error message */
    fprintf (stderr, "%s\n", strerror(errno));
    return NULL;
  }
  /* assign values to the array with the indices of the connected nodes*/
  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index_aux][i] == TRUE) {
      array[j++] = i;
    }
  }
  return array;
}

/*-----------------------------------------------------------------------------
Nombre: graph_init
Descripcion: inicializa un grafo
Argumentos de entrada: ninguno
Retorno:
- graph, puntero a graph
- NULL, en caso de error
-----------------------------------------------------------------------------*/
Graph * graph_init (){
  Graph* graph;
  graph=calloc(1, sizeof(Graph));
  if(graph==NULL){
    return NULL;
  }
  graph->plnode=list_new(node_free, node_copy, node_print, node_cmp);
  if(!graph->plnode){
    graph_free(graph);
    return NULL;
  }
  return graph;
}

/*-----------------------------------------------------------------------------
Nombre: graph_free
Descripcion: libera un grafo
Argumentos de entrada:
1. g, el puntero al grafo que se desea liberar
Retorno: nada
-----------------------------------------------------------------------------*/
void graph_free (Graph *g){
  if(g==NULL){
    return;
  }
  list_free(g->plnode);
  free(g);
  return;
}

/*-----------------------------------------------------------------------------
Nombre: graph_insertNode
Descripcion: inserta un nodo en un grafo
Argumentos de entrada:
1. g, el puntero al grafo en el que se desea insertar
2. n, el puntero al nodo correspondiente
Retorno:
- OK, si no hay problemas
- ERROR, en caso contrario
-----------------------------------------------------------------------------*/
Status graph_insertNode (Graph *g, const Node *n){
  int index, i;
  Status st=OK;
  if((index=find_node_index(g, node_getId(n)))!=-1 || !n || !g){
      return ERROR;
  }
  st=list_pushFront(g->plnode, n);
  for(i=0; i!=graph_getNumberOfNodes(g); i++){
    g->connections[graph_getNumberOfNodes(g)][i]=FALSE;
  }
  g->num_nodes=graph_getNumberOfNodes(g)+1;
  return st;
}

/*-----------------------------------------------------------------------------
Nombre: graph_insertEdge
Descripcion: inserta una union entre nodos
Argumentos de entrada:
1. g, el puntero al grafo
2. nId1, la id del primer nodo a unir
3. nId2, la id del segundo nodo a unir
Retorno:
- OK, si no hay problemas
- ERROR, en caso contrario
-----------------------------------------------------------------------------*/
Status graph_insertEdge (Graph *g, const long nId1, const long nId2){
  Status st=OK;
  int index_aux1, index_aux2, index1, index2;
  index1=find_node_index(g, nId1);
  index2=find_node_index(g, nId2);  
  if((!g || nId1 == -1 || nId2 == -1) || index1 == -1 || index2 == -1){
    return ERROR;
  }
  if(graph_areConnected(g, nId1, nId2)==TRUE){
    return st;
  }

  index_aux1=g->num_nodes-index1-1;
  index_aux2=g->num_nodes-index2-1;
  g->connections[index_aux1][index_aux2]=TRUE;
  /*node_setNConnect(g->nodes[find_node_index(g, nId1)], node_getNConnect(g->nodes[find_node_index(g, nId1)])+1);*/
  st=node_setNConnect(list_getElementInPos(g->plnode, index1), node_getNConnect(list_getElementInPos(g->plnode, index1))+1 );
  return st;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNode
Descripcion: obtiene un nodo del grafo
Argumentos de entrada:
1. g, el puntero al grafo
2. nId, la id del nodo que se desea obtener
Retorno:
- nodo, la direccion del nodo que se deseaba obtener
- NULL, en caso de error
-----------------------------------------------------------------------------*/
Node *graph_getNode (const Graph *g, long nId){
  Node *nodo;
  if(!g || nId==-1){
    return NULL;
  }
  nodo=node_copy(list_getElementInPos(g->plnode, find_node_index(g, nId)));
  return nodo;
}

/*-----------------------------------------------------------------------------
Nombre: graph_setNode
Descripcion: actualiza los valores de un nodo
Argumentos de entrada:
1. g, el nodo que se desea actualizar
2. n, el grafo en el que se desea actualizar
Retorno:
- OK, si no hay errores
- ERROR, en caso contrario
-----------------------------------------------------------------------------*/
Status graph_setNode (Graph *g, const Node *n){
  Node* aux;
  Status st=OK;
  if(!g || !n){
    return ERROR;
  }
  aux=list_getElementInPos(g->plnode, find_node_index(g, node_getId(n)));  /*g->nodes[find_node_index(g, node_getId(n))]=node_copy(n);*/
  st=node_setId(aux, node_getId(n));
  if(st==ERROR){
    goto fin;
  }
  st=node_setLabel(aux, node_getLabel(n));
  if(st==ERROR){
    goto fin;
  }
  st=node_setName(aux, node_getName(n));
  if(st==ERROR){
    goto fin;
  }
  st=node_setNConnect(aux, node_getNConnect(n));
  if(st==ERROR){
    goto fin;
  }
  st=node_setPredecessorId(aux, node_getPredecessorId(n));
  fin:
  return st;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNodesId
Descripcion: obtener las Id de los nodos de un grafo
Argumentos de entrada:
1. g, el grafo del que se desea obtener las Id de sus nodos
Retorno:
- tabla, una tabla con las id
- NULL, en caso de error
-----------------------------------------------------------------------------*/
long * graph_getNodesId (const Graph *g){
  long *tabla;
  int i;
  if(!g){
    return NULL;
  }
  tabla=calloc(graph_getNumberOfNodes(g), sizeof(long));
  if(tabla==NULL){
    return NULL;
  }
 for(i=0; i!=graph_getNumberOfNodes(g); i++){
    tabla[i]=node_getId(list_getElementInPos(g->plnode, i));
  }
  return tabla;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNumberOfNodes
Descripcion: obtiene el numero de nodos de un grafo
Argumentos de entrada:
1. g, el grafo del que se desea conocer su numero de nodos
Retorno:
- num_nodes, el numero de nodos del grafo
- -1, en caso de error
-----------------------------------------------------------------------------*/
int graph_getNumberOfNodes (const Graph *g) {
  if(!g){
    return -1;
  }
  return g->num_nodes;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNumberOfEdges
Descripcion: obtiene el numero de conexiones de un grafo
Argumentos de entrada:
1. g, el grafo del que se desea conocer el numero de conexiones
Retorno:
- num_edges, el numero de conexiones del grafo
- -1, en caso de error
-----------------------------------------------------------------------------*/
int graph_getNumberOfEdges (const Graph *g) {
  if(!g){
    return -1;
  }
  return g->num_edges;
}

/*-----------------------------------------------------------------------------
Nombre: graph_areConnected
Descripcion: comprueba si dos nodos estan conectados
Argumentos de entrada:
1. g, el grafo en el que se encuentran dos nodos
2. nId1, la id del primer nodo
3. nId1, la id del segundo nodo
Retorno:
- TRUE, si estan conectados
- FALSE, si no estan conectados
-----------------------------------------------------------------------------*/
Bool graph_areConnected (const Graph *g, const long nId1, const long nId2) {
  int index_aux1, index_aux2;
  if(!g || nId1==-1 || nId2==-1){
    return FALSE;
  }
  index_aux1=g->num_nodes-find_node_index(g, nId1)-1;
  index_aux2=g->num_nodes-find_node_index(g, nId2)-1;
  if((g->connections[index_aux1][index_aux2])==TRUE) {
    return TRUE;
  }
  return FALSE;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNumberOfConnectiosFrom
Descripcion: obtiene el numero de conexiones de un nodo
Argumentos de entrada:
1. g, el grafo en el que se encuentra el nodo
2. fromId, la id del nodo del que se desea conocer su numero de conexiones
Retorno:
- cont, el numero de conexiones del nodo
- -1, en caso de error
-----------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId) {
  int i, aux, cont;
  aux=find_node_index(g, fromId);
  if(!g || fromId==-1 || aux==-1){
    return -1;
  }
  for(i=cont=0; i!=g->num_nodes; i++){
    if((graph_areConnected(g, fromId, node_getId(list_getElementInPos(g->plnode, i))))==TRUE){
      cont++;
    }
  }
  return cont;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getConnectionsFrom
Descripcion: devuelve los id de los nodos conectados a un nodo
Argumentos de entrada:
1. g, el puntero al grafo
2. fromId, la id de un nodo
Retorno:
- tabla, una tabla con los id de los nodos
- NULL, en caso de error
-----------------------------------------------------------------------------*/
long* graph_getConnectionsFrom (const Graph *g, const long fromId) {
  int i, z;
  long* tabla;
  if(!g){
    return NULL;
  }
  if((tabla=calloc(graph_getNumberOfConnectionsFrom(g, fromId), sizeof(long)))==NULL){
    return NULL;
  }
  /*for(i=z=0; i!=graph_getNumberOfNodes(g); i++){
    if((graph_areConnected(g, fromId ,node_getId(list_getElementInPos(g->plnode, i))))==TRUE){
      tabla[z]=node_getId(list_getElementInPos(g->plnode, i));
      z++;
    }
  }*/
  for(i=graph_getNumberOfNodes(g), z=0; i!=-1; i--){
    if((graph_areConnected(g, fromId ,node_getId(list_getElementInPos(g->plnode, i))))==TRUE){
      tabla[z]=node_getId(list_getElementInPos(g->plnode, i));
      z++;
    }
  }
  return tabla;
}

/*-----------------------------------------------------------------------------
Nombre: graph_print
Descripcion: imprime los datos de un grafo
Argumentos de entrada:
1. pf, el dispositivo en el que se desea imprimir los valores
2. g, el grafo del que se desea imprimir sus datos
Retorno:
- cont, en numero de caracteres leidos
- -1, en caso de error
-----------------------------------------------------------------------------*/
int graph_print (FILE *pf, const Graph *g) {
  int i, cont, j;
  if(!g){
    return -1;
  }
  fprintf(pf, "Grafo\n");
  for(i=cont=0; i!=graph_getNumberOfNodes(g); i++){
    cont+=node_print(pf, list_getElementInPos(g->plnode, i));
    if(node_getNConnect(list_getElementInPos(g->plnode, i))>0) {
      for(j=0; j!=graph_getNumberOfNodes(g); j++) {
        if(g->connections[i][j]==TRUE)
        cont+=fprintf(pf, " %ld",  node_getId(list_getElementInPos(g->plnode, j)));
      }
    }
    cont+=fprintf(pf, "\n");
  }
  return cont;
}

/*-----------------------------------------------------------------------------
Nombre: graph_readFromFile
Descripcion: lee la informacion de un grafo de un fichero
Argumentos de entrada:
1. fin, el puntero al fichero del que leer
2. g, el puntero al grafo
Retorno:
- OK, si funciona correctamente
- ERROR, en caso de error
-----------------------------------------------------------------------------*/
Status graph_readFromFile (FILE *fin, Graph *g){
  int id_in, id, label, id_out, num, i=0;
  char nombre[64];
  Node *nodo;
  if(!fin || !g){
    return ERROR;
  }
  fscanf(fin, "%d", &num);
  while (i!=num){
    fscanf(fin, "%d %s %d", &id, nombre, &label);
    nodo = node_init();
    node_setId(nodo, id);
    node_setName(nodo, nombre);
    node_setLabel(nodo, label);
    graph_insertNode(g, nodo);
    free(nodo);
    i++;
  }
  while(fscanf(fin, "%d %d", &id_in, &id_out)==2){
    graph_insertEdge(g, id_in, id_out);
  }
  
  return OK;
}
