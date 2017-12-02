// GraphTest.c
// client to test Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(){
	Graph A = newGraph(5);
	addArc(A, 2, 1);
	addArc(A, 3, 5);
	addArc(A, 3, 2);
	addArc(A, 4, 3);
	addArc(A, 1, 4);

	printGraph(stdout, A);										// 1: 4
																// 2: 1
																// 3: 2 5
																// 4: 3
																// 5:

	printf("Order: %d\n", getOrder(A));							// should be 5
	printf("Size: %d\n", getSize(A));							// should be 5

	List S = newList();
	for (int i = 1; i < 6; i++){
		append(S, i);
	}

	DFS(A, S);
	printf("\n");
	printf("Discovery time of 5: %d\n", getDiscover(A, 5));		// should be 6
	printf("Finish time of 5: %d\n", getFinish(A, 5));			// should be 7
	printf("Parent of 3: %d\n", getParent(A, 3));				// should be 4

	printList(stdout, S);										// should be 1 4 3 2 5 
	printf("\n");

	Graph B = copyGraph(A);

	makeNull(A);
	printGraph(stdout, A);										// 1: 
																// 2: 
																// 3:
																// 4:
																// 5:

	printf("\n Graph B is a copy of A before makeNull()\n");
	printGraph(stdout, B);
																// 1: 4
																// 2: 1
																// 3: 2 5
																// 4: 3
																// 5: 

	Graph C = transpose(B);

	printf("\n Graph C is the transpose of B\n");
	printGraph(stdout, C);
																// 1: 2
																// 2: 3
																// 3: 4
																// 4: 1
																// 5: 3
}