// FindComponents.c
// Diego Magdaleno
// dmmagdal
// client to use Graph ADT and run DFS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 100

int main(int argc, char *argv[]){
	// check command line for correct number of arguments
	if (argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *in, *out;									// pointers to input and output files	

	// open files for reading and writing
	in = fopen(argv[1], "r");						// open input file to read
	out = fopen(argv[2], "w");						// open output file to write to
	if (in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int graphSize;									// hold graph size for new graph
	fscanf(in, "%d", &graphSize);					// read first line of file
	Graph G = newGraph(graphSize);					// create new graph
	int v1 = 0;
	int v2 = 0;

	// read the array to perform operations
	while (fgetc(in) != 0){
		fscanf(in, "%d", &v1);
		fscanf(in, "%d", &v2);
		if (v1 == 0){
			break;
		}
		else {
			addArc(G, v1, v2);
		}
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");

	List S = newList();
	for (int i = 1; i <= graphSize; i++){
		append(S, i);
	}

	DFS(G, S);
	Graph GTranspose = transpose(G);
	DFS(GTranspose, S);
 
	int j;
	List *Component = calloc((graphSize+1), sizeof(List));
	if (length(S) != 0){
		j = 1;
		moveBack(S);
		Component[j] = newList();
		while (index(S) != -1){
			prepend(Component[j], get(S));
			if (getParent(GTranspose, get(S)) == NIL){
				if (index(S) != 0){
					j++;
					Component[j] = newList();
				}
			}
			movePrev(S);
		}
	}

	fprintf(out, "G contains %d strongly connected components:\n", j);
	for (int l = 1; l <= j; l++){
		fprintf(out, "Component %d: ", l);
		printList(out, Component[l]);
		fprintf(out, "\n");
	}
	

	// clean up te memory
	for (int k = 1; k <= j; k++){
		freeList(&(Component[k]));
	}
	
	freeList(&S);
	free(Component);
	makeNull(G);
	freeGraph(&G);
	makeNull(GTranspose);
	freeGraph(&GTranspose);
	fclose(in);
	fclose(out);

	exit(EXIT_SUCCESS);
}