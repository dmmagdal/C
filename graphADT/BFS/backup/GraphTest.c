// GraphTest.c
// client to test Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(){
	Graph A = newGraph(5);
	addEdge(A, 2, 1);
	addEdge(A, 3, 5);
	addEdge(A, 3, 2);
	addEdge(A, 4, 3);
	addEdge(A, 1, 4);

	printGraph(stdout, A);										// 1: 2 4
																// 2: 1 3
																// 3: 2 4 5
																// 4: 1 3
																// 5: 3

	printf("Order: %d\n", getOrder(A));							// should be 5
	printf("Size: %d\n", getSize(A));							// should be 5
	printf("Source: %d\n", getSource(A));						// should be nil

	BFS(A, 5);
	printf("\n");
	printf("Dist: %d\n", getDist(A, 5));						// should be 0
	printf("Source: %d\n", getSource(A));						// should be 5
	printf("Distance from 1 to 5: %d\n", getDist(A, 1));		// should be 3

	List Path = newList();
	
}