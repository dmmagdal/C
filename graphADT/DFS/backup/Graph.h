// Graph.h
// Header file for Graph ADT

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
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

// getDiscover()
// returns the discovery time from the most recent DFS of vertex u or UNDEF if DFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// returns the finish time from the most recent DFS of vertex u or UNDEF if DFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);

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

// DFS()
// Runs depht first search algorithm to visit all possible nodes in the graph
void DFS(Graph G, List S);


// Other Operations

// transpose()
// return a transpose of the graph G
// pre: none
Graph transpose(Graph G);

// copyGraph()
// returns a copy of graph G
// pre: none
Graph copyGraph(Graph G);

// printGraph()
// prints data elements in graph to out
// pre: none
void printGraph(FILE* out, Graph G);

#endif