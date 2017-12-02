// Graph.h
// Header file for Graph ADT

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0
#include "List.h"

// Exported type
typedef struct GraphObj* Graph;


// Constructor-Destructor

// newGraph()
// returns reference to new GraphObj representing a graph with n vertices and no edges
Graph newGraph(int n);

// freeGraph()
// frees all dynamic memory associated with the Graph *pG and sets the handle *pG to NULL
void freeGraph(Graph* pG);


// Access functions

// getOrder()
// return the order of the graph
// pre: none
int getOrder(Graph G);

// getSize()
// return the size of the graph
// pre: none
int getSize(Graph G);

// getSource()
// return the source vertex most recently used in BFS() or NIL if BFS has not yet been called
// pre: 1 <= u <= getOrder(G)
int getSource(Graph G);

// getParent()
// returns the distance from the most recent BFS source to vertex u or INF if BFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// returns the distance from the most recent BFS source to vertex u or INF if BFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// appends to the List L the vertices of the shortest path in G from source u or appends to L the value NIL if no such path exists
// pre: getSource(G) != NIL, BFS() must be called before getPath()
void getPath(List L, Graph G, int u);


// Manipulation Procedures

// makeNull()
// deletes all edges of G, setting graph to no edge state
// pre: none
void makeNull(Graph G);

// addEdge()
// insert a new edge required to maintain these listsl in sorted order by increasing labels
// pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// insert a new directed edge from u to v (ie. v is added to the adjacency List of U but not u to the adjacency List of v)
// pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// runs breadth first search algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G to the file pointed to by out
void BFS(Graph G, int s);


// Other Operations

// printGraph()
// prints data elements in graph to out
// pre: none
void printGraph(FILE* out, Graph G);

#endif