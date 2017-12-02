// Findpath.c
// Diego Magdaleno
// dmmagdal
// client to use Graph ADT and find shortest path

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
			addEdge(G, v1, v2);
		}
	}

	printGraph(out, G);

	while (fgetc(in) != 0){
		fscanf(in, "%d", &v1);
		fscanf(in, "%d", &v2);
		if (v1 == 0){
			break;
		}
		else {
			List path = newList();
			BFS(G, v1);
			getPath(path, G, v2);
			if (getDist(G, v2) == INF){
				fprintf(out, "The distance from %d to %d is infinity\n", v1, v2);
				fprintf(out, "No %d-%d path exists\n", v1, v2);
			}
			else {
				fprintf(out, "The distance from %d to %d is %d\n", v1, v2, getDist(G, v2));
				fprintf(out, "A shortest %d-%d path is: ", v1, v2);
				printList(out, path);
			}
			fprintf(out, "\n");
		}	
	}

	// clean up te memory
	makeNull(G);
	freeGraph(&G);
	fclose(in);
	fclose(out);

	exit(EXIT_SUCCESS);
}