/**************************************************
Nombre del modulo: graph_option2.c
Descripcion: Implementacion del TAD graph con distinta estructura
Autor:  
Fecha: 07-05-20
Modulos propios que necesita: list.h node.h graph_option1.h stack_types.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/
#include "list.h"
#include "node.h"
#include "graph_option1.h"
#include "stack_types.h"


/*=== Definiciones ==========================================================*/
#define MAX_NODES 1064

struct _Graph {
Node **nodes; /*!<Static array with the graph nodes */
List **plconnect; /*!<Adjacency static array list */
int num_nodes; /*!<Total number of nodes in the graph */
int num_edges; /*!<Total number of connections in the graph */
int capacity;
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
    if(node_getId(g->nodes[i])==nId1)
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
- con, el array con los indices
-----------------------------------------------------------------------------*/
int* graph_getConnectionsIndex(const Graph *g, int index){
  int *con, size;
  int i=0, j=0;
  if(!g || index<0 || index>=g->num_nodes)
    return NULL;
  size=node_getNConnect(g->nodes[i]);
  con = calloc(size, sizeof(int));
  if(!con)
    return NULL;
  for(i=0; i!=size; i++){
    con[j++]=*(int*)list_getElementInPos(g->plconnect[index], i);
  }
  return con;
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
  graph->capacity=2;
  graph->nodes=(Node**)calloc(graph->capacity, sizeof(Node*));  
  graph->plconnect=(List**)calloc(graph->capacity, sizeof(List*));
  /*for(i=graph->num_nodes; i!=graph->capacity; i++){
    graph->nodes[i]=node_init();
    graph->plconnect[i]=list_new(int_free, int_copy, int_print, int_cmp);
  }*/
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
  int i;
  if(g==NULL){
    return;
  }
  for(i=0; i!=g->num_nodes; i++){
    node_free(g->nodes[i]);
    list_free(g->plconnect[i]);
  }
  free(g->nodes);
  free(g->plconnect);
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
Status graph_insertNode(Graph *g, const Node *n){
  int index;
  if((index=find_node_index(g, node_getId(n)))!=-1 || !n || !g){
      return ERROR;
  }
  if(g->capacity==g->num_nodes){
    g->nodes=realloc(g->nodes, g->capacity*2*sizeof(Node*));
    g->plconnect=realloc(g->plconnect, g->capacity*2*sizeof(g->plconnect));
    g->capacity*=2;
  }
  g->nodes[g->num_nodes]=node_copy(n);
  if(!(g->plconnect[g->num_nodes]=list_new(int_free, int_copy, int_print, int_cmp)))
    return ERROR;
  g->num_nodes++;
  return OK;
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
Status graph_insertEdge(Graph *g, const long nId1, const long nId2){
  Status st=OK;
  int z;
  z=find_node_index(g, nId1);
  if(g==NULL || nId1 == -1 || nId2 == -1 || z==-1)
    return ERROR;
  if(graph_areConnected(g, nId1, nId2)==TRUE){
    return st;
  }
  st=list_pushOrder(g->plconnect[z], &nId2, 1);
  if(st==OK)
    g->num_edges++;
  st=node_setNConnect(g->nodes[z], node_getNConnect(g->nodes[z])+1);
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
Node *graph_getNode(const Graph *g, long nId){
  int i=0;
  Node *nodo=NULL;
  if(!g)
    return NULL;
  i=find_node_index(g, nId);
  if(i==-1)
    return NULL;
  /*if((i=find_node_index(g, nId))==-1)
    return NULL;*/
  return nodo=node_copy(g->nodes[i]);
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
  aux=g->nodes[find_node_index(g, node_getId(n))];
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
long *graph_getNodesId (const Graph *g){
  long *tabla;
  int i;
  if(!g){
    return NULL;
  }
  if(!(tabla=calloc(g->num_nodes, sizeof(long))))
    return NULL;
  for(i=0; i!=g->num_nodes; i++){
    tabla[i]=node_getId(g->nodes[i]);
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
Bool graph_areConnected (const Graph *g, const long nId1, const long nId2){
  int i, z;
  if(!g){
    return FALSE;
  }
  z=find_node_index(g, nId1);
  i=list_getPositionElement(g->plconnect[z], &nId2);
  if(i==-1){
    return FALSE;
  }
  return TRUE;
}

/*-----------------------------------------------------------------------------
Nombre: graph_getNumberOfConnectiosFrom
Descripcion: obtiene el numero de conexiones de un nodo
Argumentos de entrada:
1. g, el grafo en el que se encuentra el nodo
2. fromId, la id del nodo del que se desea conocer su numero de conexiones
Retorno:
- el numero de conexiones del nodo
- -1, en caso de error
-----------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
  int i;
  if(!g)
    return -1;
  if((i=find_node_index(g, fromId))==-1)
    return -1;
  return list_size(g->plconnect[i]);
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
long* graph_getConnectionsFrom (const Graph *g, const long fromId){
  long* tabla;
  int i, z, j;
  if(!g)
    return NULL;
  if((z=find_node_index(g, fromId))==-1)
    return NULL;
  if(!(tabla=calloc(graph_getNumberOfConnectionsFrom(g, fromId), sizeof(long))))
    return NULL;
  j=list_size((g->plconnect[z]));
  for(i=0; i!=j; i++){
    tabla[i]=*(long*)list_getElementInPos(g->plconnect[z], i);
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
    cont+=node_print(pf, g->nodes[i]);
    if(node_getNConnect(g->nodes[i])>0) {
      for(j=0; j!=graph_getNumberOfNodes(g); j++) {
        if(graph_areConnected(g, node_getId(g->nodes[i]),  node_getId(g->nodes[j]))==TRUE)
        cont+=fprintf(pf, " %ld",  node_getId(g->nodes[j]));
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
