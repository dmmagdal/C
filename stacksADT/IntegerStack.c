// IntegerStack.c
// linkedlist implementation for atack storing integers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "IntegerStack.h"

// private types

// NodeObj
typedef struct NodeObj{
	int item;				// stores the int in item
	struct NodeObj* next; 	// pointer to next
} NodeObj;

// Node
typedef NodeObj* Node; 		// pointer to Node

// newNode()
// constructor of Node type
Node newNode(int x){
	Node N = malloc(sizeof(NodeObj));	// allocate memory of size NodeObj to Node N
	assert(N != NULL);					// N is never null
	N->item = x;						// set N.item to be x
	N->next = NULL;						// set N.next = null
	return N;							// return to completed Node
}

// freeNode()
// destructor of Node type
void freeNode(Node* pN){
	if (pN != NULL && *pN != NULL){
		free(*pN);						// free the memory of the node pointer
		*pN = NULL;						// set the node pointer to null
	}
}

// stackObj;
typedef struct stackObj{
	Node top;				// stores the node pointing to the top of the stack
	int numItems;			// store the number of items in the stack
} stackObj;

// public functions

// newStack()
// constructor of the Stack type
Stack newStack(void){
	Stack S = malloc(sizeof(stackObj));	// similar operations to node constructor
	assert(S != NULL);
	S->top = NULL;						// set the top = null
	S->numItems = 0;					// set the nuber of items = 0
	return S;
}

// freeStack()
// desctructor of the Stack type
void freeStack(Stack* pS){
	if (pS != NULL && *pS != NULL){ 	// again, very similar operations to node destructor
		if (!isEmpty(*pS)){				// if the stack is not empty
			popAll(*pS);				// pop all the items
		}
		free(*pS);
		*pS = NULL;
	}
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Stack S){
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling isEmpty() on NULL Stack reference\n");			// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	return(S->numItems == 0); 			// return if the number of items in the stack = 0
}

// push()
// push x onto the top of stack S
// pre: none
void push(Stack S, int x){
	Node N;
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling push() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	N = newNode(x);						// create new node to hold x
	N->next = S->top;					// set N.next = top of the stack
	S->top = N;							// set the top of the stack to N
	S->numItems++;						// increment the number of items
}

// pop()
// deletes and returns the item at the top of the stack
// pre: !isEmpty(S)
int pop(Stack S){ // note that the return type matches the type of the object returned
	int returnvalue; 					// same thing about note above
	Node N;
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling pop() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (S->numItems == 0){																		// if number of items = 0 (S is empty)
		fprintf(stderr, "Stack Error: calling pop() on empty Stack\n");						// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}																						
	N = S->top;							// use place holder N to hold top of stack 
	returnvalue = S->top->item;			// set returnvalue to the item at the top of the stack
	S->top = S->top->next;				// set top of stack to item next item after it
	S->numItems--;						// decrement the number of items
	freeNode(&N);						// deallocate/free N in order to free the old top node
	return returnvalue;					// return the returnvalue
}

// peek()
// returns the item at the top of the stack
// pre: !isEmpty(S)
int peek(Stack S){
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling peek() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (S->numItems == 0){																		// if number of items = 0 (S is empty)
		fprintf(stderr, "Stack Error: calling peek() on empty Stack\n");						// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}	
	return S->top->item;				// return the item at the top of the stack
}

// popAll()
// empty the stack
// pre: !isEmpty(S)
void popAll(Stack S){
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling popAll() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (S->numItems == 0){																		// if number of items = 0 (S is empty)
		fprintf(stderr, "Stack Error: calling popAll() on empty Stack\n");						// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	while (S->numItems != 0){			// while the stack is not empty
		pop(S);							// pop()
	}
}

// printStack()
// prints out the stack to the file pointed by out
// pre: none
void printStack(FILE* out, Stack S){
	Node N;
	if (S == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling popStack() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	for (N = S->top; N != NULL; N = N->next){	// iterate through the stack with N
		fprintf(out, "%d ", N->item);			// print N.item to out (Note: %d means it prints an int, which is the type N.item is)
	}
	fprintf(out, "\n");
}