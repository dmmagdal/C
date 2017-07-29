// IntegerStackClient.c
// Test client for IntegerStack ADT

#include <stdio.h>
#include <stdlib.h>
#include "IntegerStack.h"

int main(int argc, char* argv[]){
	Stack A = newStack();
	Stack B = newStack();

	// push items onto stack A
	push(A, 5);
	push(A, 3);
	push(A, 9);
	push(A, 7);
	push(A, 8);

	// print stack A
	printStack(stdout, A);

	// peek A
	printf("%d\n", peek(A));

	// pop A
	pop(A);
	pop(A);
	pop(A);

	// peek A
	printf("%d\n", peek(A));

	// are the stacks empty?
	printf("%s\n", isEmpty(A) == 0?"false":"true");
	printf("%s\n", isEmpty(A) == 0?"false":"true");

	// push items onto stack B
	push(B, 5);
	push(B, 3);

	push(A, 12);

	push(B, 13);

	// print the stacks
	printStack(stdout, A);
	printStack(stdout, B);

	// clear A
	popAll(A);

	// print stack A
	printStack(stdout, B);

	// clear the memory
	freeStack(&A);
	freeStack(&B);
	return EXIT_SUCCESS;
}