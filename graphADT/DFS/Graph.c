// Graph.c
// Array of List implementation of Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
void Visit(Graph G, List S, int v);

// structs

// private GraphObj type
typedef struct GraphObj{
	int size;
	int order;
	int time;
	char* color;
	int* d;
	int* f;
	int* p;
	List* vertex;
} GraphObj;


// Constructor-Destructor

// newGraph()
// returns reference to new GraphObj representing a graphe with n vertices and no edges
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->time = 0;
	G->color = calloc((n+1), sizeof(char));
	G->d = calloc((n+1), sizeof(int));
	G->f = calloc((n+1), sizeof(int));
	G->p = calloc((n+1), sizeof(int));
	G->vertex = calloc((n+1), sizeof(List));
	for (int i = 1; i <= n; i++){
		G->vertex[i] = newList();
		G->color[i] = 'w';
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
		G->p[i] = NIL;
	}
	return(G);
}

// freeGraph()
// frees all dynamic memory associated with the Graph *pG and sets the handle *pG to NULL
void freeGraph(Graph* pG){
	if (pG != NULL && *pG != NULL){
		for (int i = 1; i <= getOrder(*pG); i++){
			if (length((*pG)->vertex[i]) != 0){
				clear((*pG)->vertex[i]);
			}
			freeList(&(*pG)->vertex[i]);
		}
		free((*pG)->p);
		free((*pG)->d);
		free((*pG)->f);
		free((*pG)->color);
		free((*pG)->vertex);
		free(*pG);
		*pG = NULL;
	}
}


// Access functions

// getOrder()
// return the order of the graph
// pre: none
int getOrder(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return(G->order);
}

// getSize()
// return the size of the graph
// pre: none
int getSize(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return(G->size);
}

// getParent()
// returns the distance from the most recent BFS source to vertex u or INF if DFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	else if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: Using invalid target vertex in getParent()\n");
		exit(1);
	}
	return(G->p[u]);
}

// getDiscover()
// returns the discovery time from the most recent DFS of vertex u or UNDEF if DFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	else if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: Using invalid target vertex in getDist()\n");
		exit(1);
	}
	return(G->d[u]);
}

// getFinish()
// returns the finish time from the most recent DFS of vertex u or UNDEF if DFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getFinish() on NULL Graph reference\n");
		exit(1);
	}
	else if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: Using invalid target vertex in getFinish()\n");
		exit(1);
	}
	return(G->f[u]);
}


// Manipulation Procedures

// makeNull()
// deletes all edges of G, setting graph to no edge state
// pre: none
void makeNull(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling makeNull() on NULL Graph reference\n");
		exit(1);
	}
	else {
		for (int i = 1; i <= getOrder(G); i++){
			clear(G->vertex[i]);
		}
		G->size = 0;
	}
}

// addEdge()
// insert a new edge required to maintain these lists in sorted order by increasing labels
// pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling addEdge() on NULL Graph reference\n");
		exit(1);
	}
	else if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)){
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
	}
}

// addArc()
// insert a new directed edge from u to v (ie. v is added to the adjacency List of U but not u to the adjacency List of v)
// pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	else if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)){
		if (length(G->vertex[u]) == 0){
			append(G->vertex[u], v);
		}
		else {
			moveFront(G->vertex[u]);
			while (index(G->vertex[u]) != -1){
				if (v < get(G->vertex[u])){
					insertBefore(G->vertex[u], v);
					moveBack(G->vertex[u]);
					moveNext(G->vertex[u]);
				}
				else if (v == get(G->vertex[u])){
					moveBack(G->vertex[u]);
					moveNext(G->vertex[u]);
				}
				else if (v > get(G->vertex[u]) && index(G->vertex[u]) == length(G->vertex[u])-1){
					append(G->vertex[u], v);
					moveBack(G->vertex[u]);
					moveNext(G->vertex[u]);
				}
				else{
					moveNext(G->vertex[u]);
				}
			}
		}
		G->size++;
	}
}

// DFS()
// Runs depht first search algorithm to visit all possible nodes in the graph
// pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
	if (length(S) != getOrder(G)){
		fprintf(stderr, "Graph Error: Calling DFS() on List of wrong size. List must be of same length as the graph's order\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++){
		G->color[i] = 'w';
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
	}
	G->time = 0;
	List CopyS = copyList(S);
	moveFront(CopyS);
	// while (index(CopyS) != -1){
	for (int j = 0; j < length(S); j++){
		if (G->color[get(CopyS)] == 'w'){
			Visit(G, S, get(CopyS));
		}
		moveNext(CopyS);
	}
	freeList(&CopyS);
}

// Visit()
// executes the recursive visit() component of DFS
// pre: none
void Visit(Graph G, List S, int v){
	G->color[v] = 'g';
	G->d[v] = ++G->time;
	if (length(G->vertex[v]) != 0){
		moveFront(G->vertex[v]);
		// while (index(G->vertex[v]) != -1){
		for (int i = 0; i < length(G->vertex[v]); i++){
			if (G->color[get(G->vertex[v])] == 'w'){
				G->p[get(G->vertex[v])] = v;
				Visit(G, S, get(G->vertex[v]));
			}
			moveNext(G->vertex[v]);
		}
	}
	G->color[v] = 'b';
	G->f[v] = ++G->time;
	prepend(S, v);
	deleteBack(S);
}


// Other Operations

// transpose()
// return a transpose of the graph G
// pre: none
Graph transpose(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling transpose() on NULL Graph reference\n");
		exit(1);
	}
	Graph trans = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++){
		if (length(G->vertex[i]) == 0){
			continue;
		}
		else {
			moveFront(G->vertex[i]);
			while (index(G->vertex[i]) != -1){
				addArc(trans, get(G->vertex[i]), i);
				moveNext(G->vertex[i]);
			}
		}
	}
	return(trans);
}

// copyGraph()
// returns a copy of graph G
// pre: none
Graph copyGraph(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling copyGraph() on NULL Graph reference\n");
		exit(1);
	}
	Graph copy = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++){
		if (length(G->vertex[i]) == 0){
			continue;
		}
		else {
			moveFront(G->vertex[i]);
			while (index(G->vertex[i]) != -1){
				addArc(copy, i, get(G->vertex[i]));
				moveNext(G->vertex[i]);
			}
		}
	}
	return(copy);
}

// printGraph()
// prints data elements in graph to out
// pre: none
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling printGraph() on NULL Graph reference\n");
		exit(1);
	}
	else{
		for (int i = 1; i <= getOrder(G); i++){
			fprintf(out, "%d: ", i);
			printList(out, G->vertex[i]);
			fprintf(out, "\n");
		}
	}
}