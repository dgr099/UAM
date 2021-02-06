/**************************************************
Nombre del módulo: graph.c
Descripción:	Funciones necesarias para trabajar con grafos
Autor:	 
Fecha:	jue, 13 de feb de 2020
Módulos propios que necesita:	node.h
Notas:	pregunta graph_getConnectionsFrom
Modificaciones:
Mejoras pendientes:
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

# define MAX_NODES 1064

struct _Graph {
Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
int num_nodes; /*!<Total number of nodes in te graph */
int num_edges; /*!<Total number of connection in the graph */
};
/**
   Private functions
*/
int find_node_index (const Graph * g, int nId1);
int* graph_getConnectionsIndex (const Graph * g, int index);

/* It returns the index of the node with id nId1 */
int find_node_index (const Graph * g, int nId1) {
int i;
if (!g) return -1;
for(i=0; i < g->num_nodes; i++) {
if (node_getId (g->nodes[i]) == nId1) return i;
}
/* ID not found*/
return -1;
}
/* It returns an array with the indices of the nodes cgonnected to the node */
/* whose index is index */
/* It also allocates memory for the array. */
int* graph_getConnectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size;
  if (!g) return NULL;
  if (index < 0 || index >g->num_nodes) return NULL;
  /* get memory for the array */
  size = node_getNConnect (g->nodes[index]);
  array = (int *) malloc(sizeof (int) * size);
  if (!array) {
  /* print error message */
    fprintf (stderr, "%s\n", strerror(errno));
    return NULL;
  }
  /* assign values to the array with the indices of the connected nodes*/
  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
      array[j++] = i;
    }
  }
  return array;
}
/*------------------------------
Nombre:	graph_init
Descripción:	inicializacion de un grafo
Argumentos de entrada:	ninguno
Retorno:	la dirección de un grafo
-------------------------------*/
Graph * graph_init (){
  Graph* graph;
  graph=calloc(1, sizeof(Graph));
  if(graph==NULL){
    return NULL;
  }
  return graph;
}
/*------------------------------
Nombre: graph_free
Descripción:  liberación de un grafo
Argumentos de entrada:  el grafo que se desea liberar
Retorno: 
-------------------------------*/
void graph_free (Graph *g){
  int i;
  if(g==NULL){
    return;
  }
  for(i=0; g->nodes[i]!=NULL; i++){
    node_free(g->nodes[i]);
  }
  free(g);
  return;
}
/*------------------------------
Nombre:	graph_insertNode
Descripción:  insertar un nodo en un grafo
Argumentos de entrada:  el grafo en el que se desea insertar y el nodo correspondiente
Retorno:  OK si no hay problemas, ERROR en caso contrario
-------------------------------*/
Status graph_insertNode (Graph *g, const Node *n){
  int index, i;
  if((index=find_node_index(g, node_getId(n)))!=-1 || !n || !g){
      return ERROR;
  }
  g->nodes[graph_getNumberOfNodes(g)]=node_copy(n);
  for(i=0; i!=graph_getNumberOfNodes(g); i++){
    g->connections[graph_getNumberOfNodes(g)][i]=FALSE;
  }
  g->num_nodes=graph_getNumberOfNodes(g)+1;
  return OK;
}
/*------------------------------
Nombre:	graph_insertEdge
Descripción:  insertar una unión entre nodos
Argumentos de entrada:  la id de los nodos que se desean unir y el grafo en el que se encuentran
Retorno:  OK si no hay problemas, ERROR en caso contrario
-------------------------------*/
Status graph_insertEdge (Graph *g, const long nId1, const long nId2){
  if((!g || nId1 == -1 || nId2 == -1) || find_node_index(g, nId1) != -1 || find_node_index(g, nId2)!= -1){
    return ERROR;
  }
  g->connections[find_node_index(g, nId1)][find_node_index(g, nId2)]=TRUE;
  node_setNConnect(g->nodes[find_node_index(g, nId1)], node_getNConnect(g->nodes[find_node_index(g, nId1)])+1);
  return OK;
}
/*------------------------------
Nombre:	graph_getNode
Descripción:  obtener un nodo del grafo
Argumentos de entrada:  la id del nodo que se desea obtener y el grafo en el que se encuentra
Retorno:  la dirección del nodo que se deseaba
-------------------------------*/
Node *graph_getNode (const Graph *g, long nId){
  Node *nodo;
  if(!g || nId==-1){
    return NULL;
  }
  nodo=node_copy(g->nodes[find_node_index(g, nId)]);
  return nodo;
}
/*------------------------------
Nombre:	graph_setNode
Descripción:  actualizar los valores de un nodo
Argumentos de entrada:  el nodo que se desea actualizar y el grafo en el que se desea actualizar
Retorno:  Ok si no hay errores, ERROR en caso contrario
-------------------------------*/
Status graph_setNode (Graph *g, const Node *n){
  if(!g || !n){
    return ERROR;
  }
  node_free(g->nodes[find_node_index(g, node_getId(n))]);
  g->nodes[find_node_index(g, node_getId(n))]=node_copy(n);
  return OK;
}
/*------------------------------
Nombre:	graph_getNodesId
Descripción:  obtener las Id de los nodos de un grafo
Argumentos de entrada:  el grafo del que se desea obtener las Id de sus nodos
Retorno:  una tabla con las Id
-------------------------------*/
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
    tabla[i]=node_getId(g->nodes[i]);
  }
  return tabla;
}
/*------------------------------
Nombre:	graph_getNumberOfNodes
Descripción:  obtener el numero de nodos de un grafo
Argumentos de entrada:  el grafo del que se desea conocer su número de nodos
Retorno:  el número de nodos del grafo
-------------------------------*/
int graph_getNumberOfNodes (const Graph *g) {
  if(!g){
    return ERROR;
  }
  return g->num_nodes;
}
/*------------------------------
Nombre:	graph_getNumberOfEdges
Descripción:  obtener el numero de conexiones de un grafo
Argumentos de entrada:  el grafo del que se desea conocer el número de conexiones
Retorno:  el número de conexiones del grafo
-------------------------------*/
int graph_getNumberOfEdges (const Graph *g) {
  if(!g){
    return ERROR;
  }
  return g->num_edges;
}
/*------------------------------
Nombre:	graph_areConnected
Descripción:  saber si dos nodos estan conectados
Argumentos de entrada:  la id de los nodos que se desea saber si estan conectados y el grafo en el que se encuentran
Retorno:  True si estan conectados, False en caso contrario
-------------------------------*/
Bool graph_areConnected (const Graph *g, const long nId1, const long nId2) {
  if(!g || nId1==-1 || nId2==-1){
    return FALSE;
  }
  if((g->connections[find_node_index(g, nId1)][find_node_index(g, nId2)])==TRUE) {
    return TRUE;
  }
  return FALSE;
}
/*------------------------------
Nombre:	graph_getNumberOfConnectiosFrom
Descripción:  obtener el numero de conexiones de un nodo
Argumentos de entrada:  el nodo del que se desea conocer su numero de conexiones y el grafo en el que se encuentra
Retorno:  el numero de conexiones del nodo
-------------------------------*/
int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId) {
  int i, aux, cont;
  aux=find_node_index(g, fromId);
  if(!g || fromId==-1 || aux==-1){
    return -1;
  }
  for(i=cont=0; i!=g->num_nodes; i++){
    if((graph_areConnected(g, fromId, node_getId(g->nodes[i])))==TRUE){
      cont++;
    }
  }
  return cont;
}
/*------------------------------
Nombre:	
Descripción:
Argumentos de entrada:
Retorno:
-------------------------------*/
long* graph_getConnectionsFrom (const Graph *g, const long fromId) {
  int i, z;
  long* tabla;
  if(!g){
    return NULL;
  }
  if((tabla=calloc(graph_getNumberOfConnectionsFrom(g, fromId), sizeof(long)))==NULL){
    return NULL;
  }
  /*aux=find_node_index(g, fromId);*/
  for(i=z=0; i!=graph_getNumberOfNodes(g); i++){
    if((graph_areConnected(g, fromId ,node_getId(g->nodes[i])))==TRUE){
      tabla[z]=node_getId(g->nodes[i]);
      z++;
    }
  }
  return tabla;
}
/*------------------------------
Nombre:	graph_print
Descripción:  imprimir los datos de un grafo
Argumentos de entrada:  el dispositivo en el que se desea imprimir los valores y el grafo del que se desea imprimir sus datos
Retorno:  el numero de caracteres leidos
-------------------------------*/
int graph_print (FILE *pf, const Graph *g) {
  int i, cont, j;
  if(!g){
    return -1;
  }
  fprintf(pf, "Grafo\n");
  for(i=cont=0; i!=graph_getNumberOfNodes(g); i++){
    cont+=fprintf(pf, "[%s, %ld, %d, %d]", node_getName(g->nodes[i]), node_getId(g->nodes[i]), node_getLabel(g->nodes[i]), node_getNConnect(g->nodes[i]));
    if(node_getNConnect(g->nodes[i])>0) {
      for(j=0; j!=graph_getNumberOfNodes(g); j++) {
        if(g->connections[i][j]==TRUE)
        cont+=fprintf(pf, " %ld",  node_getId(g->nodes[j]));
      }
    }
    cont+=fprintf(pf, "\n");
  }
  return cont;
}
Status graph_readFromFile (FILE *fin, Graph *g){
  int id_in, id, label, id_out, num, i;
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