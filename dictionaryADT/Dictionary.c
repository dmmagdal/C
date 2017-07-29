// Dictionary.c
// linkedlist implementation for dictionary storing key value pairs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// private types

// NodeObj
typedef struct NodeObj{
	char* key;				// stores the key
	char* value;			// stores the associated value to the key
	struct NodeObj* next; 	// pointer to next
} NodeObj;

// Node
typedef NodeObj* Node; 		// pointer to Node

// newNode()
// constructor of Node type
Node newNode(char* k, char* v){
	Node N = malloc(sizeof(NodeObj));	// allocate memory of size NodeObj to Node N
	assert(N != NULL);					// N is never null
	N->key = k;							// set N.key to be k
	N->value = v;						// set N.value to be v
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

// dictionaryObj;
typedef struct dictionaryObj{
	Node head;				// stores the node pointing to the head of the dictionary
	int numItems;			// store the number of items in the stack
} dictionaryObj;

// public functions

// newDictionary()
// constructor of the Dictionary type
Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(dictionaryObj));	// similar operations to node constructor
	assert(D != NULL);
	D->head = NULL;						// set head = null
	D->numItems = 0;					// set the nuber of items = 0
	return D;
}

// freeDictionary()
// desctructor of the Dictionary type
void freeDictionary(Dictionary *pD){
	if (pD != NULL && *pD != NULL){ 	// again, very similar operations to node destructor
		if (!isEmpty(*pD)){				// if the dictionary is not empty
			makeEmpty(*pD);				// make it empty
		}
		free(*pD);
		*pD = NULL;
	}
}

// isEmpty()
// returns 1 (true) if D is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
	if (D == NULL){																				// if D is Null
		fprintf(stderr, "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");	// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	return(D->numItems == 0); 			// return if the number of items in the dictionary = 0
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
	return D->numItems;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no such 
// value v exits
// pre: none
char* lookup(Dictionary D, char* k){
	if (D == NULL){																				// if D is Null
		fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");	// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	Node N = D->head;					// create new node and set it to the head of the Dictionary
	char* v = NULL;						// create char* v to hold the return value, initialize it to null
	while (N != NULL){					// while N is not null
		if (N->key == k){				// if N.key = k, set v to N.value
			v = N->value;
		}
		N = N->next;					// iterate N through the dictionary
	}
	freeNode(&N);						// free N
	return v;							// return v
}


// insert()
// inserts new (key, value) pair into D
// pre: lookup(D, k) == NULL
void insert(Dictionary D, char* k, char* v){
	if (D == NULL){																				// if D is Null
		fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");	// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (lookup(D, k) != NULL){																	// if the key already exists in the dictionary
		fprintf(stderr, "Dictionary Error: calling insert() on an already existing key\n");		// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	Node N;
	N = newNode(k, v);					// create new node to hold k and v
	N->next = D->head;					// set N.next = top of the stack
	D->head = N;						// set the head of the dictionary to N
	D->numItems++;						// increment the number of items
}

// delete()
// deletes pair with key k
// pre: lookup(D, k) != nul
void delete(Dictionary D, char* k){
	Node N;
	if (D == NULL){																				// if D is Null
		fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");	// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (D->numItems == 0){																		// if number of items = 0 (S is empty)
		fprintf(stderr, "Dictionary Error: calling delete() on empty Dictionary\n");			// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}										
	if (lookup(D, k) == NULL){																	// if the target k is not in D
		fprintf(stderr, "Dictionary Error: calling delete() on a key not int the Dictionary\n");// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}												
	N = D->head;						// use place holder N and set it to the head of the dictionary
	Node Prev;							// use Prev as a place holder for the node behind N
	if (N->key == k && N == D->head){	// if the target node is at the head of the dictionary
			D->head = D->head->next;	// set the head to head.next
			freeNode(&N);				// free memory of the node deleted
	}
	while (N != NULL && N->key != k){	// while N is not null and N.key is not k, (target not found)
		Prev = N;						// set Prev to N
		N = N->next;					// iterate N to N.next
	}
	if (N != NULL){						// if N is not null (meaning we found the target node)	
		Prev->next = N->next;			// set Prev.next to N.next
	}
	freeNode(&N);						// free memory of the node deleted
	D->numItems--;						// decrement the number of items
}

// makeEmpty()
// resets D to the empty state
// pre: none
void makeEmpty(Dictionary D){
	if (D == NULL){																				// if D is Null
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	if (D->numItems == 0){																		// if number of items = 0 (S is empty)
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on empty Dictionary\n");			// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	while (D->numItems != 0){			// while the Dictionary is not empty
		delete(D, D->head->key);			// delete the head
	}
}

// printDictionary()
// prints out the dictionary to the file pointed by out
// pre: none
void printDictionary(FILE* out, Dictionary D){
	Node N;
	if (D == NULL){																				// if S is Null
		fprintf(stderr, "Stack Error: calling popStack() on NULL Stack reference\n");				// print the following error message
		exit(EXIT_FAILURE);																		// exit the program
	}
	for (N = D->head; N != NULL; N = N->next){	// iterate through the dictionary with N
		fprintf(out, "(%s, %s) ", N->key, N->value);			// print N.key and N.value to out 
	}
	fprintf(out, "\n");
}