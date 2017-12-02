// Graph.c
// Array of List implementation of Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"


// structs

// private GraphObj type
typedef struct GraphObj{
	int size;
	int order;
	char* color;
	int* d;
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
	G->color = calloc((n+1), sizeof(char));
	G->d = calloc((n+1), sizeof(int));
	G->p = calloc((n+1), sizeof(int));
	G->vertex = calloc((n+1), sizeof(List));
	for (int i = 1; i <= n; i++){
		G->vertex[i] = newList();
		G->color[i] = 'w';
		G->d[i] = INF;
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

// getSource()
// return the source vertex most recently used in BFS() or NIL if BFS has not yet been called
// pre: none
int getSource(Graph G){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	int source = NIL;
	for (int i = 1; i <= getOrder(G); i++){
		if (G->d[i] == 0){
			source = i;
			break;
		}
	}
	return(source);
}

// getParent()
// returns the distance from the most recent BFS source to vertex u or INF if BFS() has not yet been called
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

// getDist()
// returns the distance from the most recent BFS source to vertex u or INF if BFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
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

// getPath()
// appends to the List L the vertices of the shortest path in G from source u or appends to L the value NIL if no such path exists
// pre: getSource(G) != NIL, BFS() must be called before getPath()
void getPath(List L, Graph G, int u){
	if (L == NULL) {
		fprintf(stderr, "Graph Error: Calling addEdge() on NULL List reference\n");
		exit(1);
	}
	else if (G == NULL){
		fprintf(stderr, "Graph Error: Calling getPath() on NULL Graph reference\n");
		exit(1);
	}
	else if (getSource(G) != NIL){
		if (u == getSource(G)){
			append(L, u);
		}
		else if (G->p[u] == NIL){
			clear(L);
			append(L, NIL);
		}
		else{
			getPath(L, G, G->p[u]);
			append(L, u);
		}
	}
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
		for (int i = 0; i <= getOrder(G); i++){
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

// BFS()
// runs breadth first search algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G to the file pointed to by out
void BFS(Graph G, int s){
	if (G == NULL){
		fprintf(stderr, "Graph Error: Calling BFS() on NULL Graph reference\n");
		exit(1);
	}
	else if (s >= 1 && s <= getOrder(G)){
		for (int u = 1; u <= getOrder(G); u++){
			if (u == s){
				continue;
			}
			else{
				G->color[u] = 'w';
				G->d[u] = INF;
				G->p[u] = NIL;
			}
		}
		G->color[s] = 'g';
		G->d[s] = 0;
		G->p[s] = NIL;
		List L = newList();
		append(L, s);
		while (length(L) != 0){
			int u = front(L);
			deleteFront(L);
			if (length(G->vertex[u]) != 0){
				moveFront(G->vertex[u]);
				while (index(G->vertex[u]) != -1){
					int v = get(G->vertex[u]);
					if (G->color[v] == 'w'){
						G->color[v] = 'g';
						G->d[v] = G->d[u] + 1;
						G->p[v] = u;
						append(L, v);
					}
					moveNext(G->vertex[u]);
				}
			}
			G->color[u] = 'b';
		}
		clear(L);
		freeList(&L);
	}
}


// Other Operations

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