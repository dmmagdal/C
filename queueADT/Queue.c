// Queue.c
// linkedlist implementation for the Queue ADT

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


// structs

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct QueueObj{
	Node front;
	Node back;
	int numItems;
} QueueObj;


// Constructors-Destructors

// newNode()
// returns reference to new Node object. Initializes next and data fields
// Private 
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	return(N);
}

// freeNode()
// frees heap memory pointed to by *pN, sets *pN to null
// Private
void freeNode(Node* pN){
	if (pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

// newQueue()
// returns reference to new empty queue object
Queue newQueue(void){
	Queue Q;
	Q = malloc(sizeof(QueueObj));
	Q->front = Q->back = NULL;
	Q->numItems = 0;
	return(Q);
}

// freeQueue()
// frees all heap memory associated with Queue *pQ, and sets *pQ to null
void freeQueue(Queue* pQ){
	if (pQ != NULL && *pQ != NULL){
		while (!isEmpty(*pQ)){
			Dequeue(*pQ);
		}
		free(*pQ);
		*pQ = NULL;
	}
}


// Access functions

// getFront()
// returns the value at the front of Q
// pre: !isEmpty(Q)
int getFront(Queue Q){
	if (Q == NULL){
		printf("Queue Error: calling getFront() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(Q)){
		printf("Queue Error: calling getFront() on empty Queue\n");
		exit(1);
	}
	return(Q->front->data);
}

// getLength()
// returns the length of Q
int getLength(Queue Q){
	if (Q == NULL){
		printf("Queue Error: calling getLength() on NULL Queue reference\n");
		exit(1);
	}
	return(Q->numItems);
}

// isEmpty()
// returns 1 (true) if Q is empty, otherwise returns 0 (false)
int isEmpty(Queue Q){
	if (Q == NULL){
		printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
		exit(1);
	}
	return(Q->numItems == 0);
}


// Manipulation procedures

// Enqueue()
// places new data element at the end of Q
void Enqueue(Queue Q, int data){
	Node N = newNode(data);
	if (Q == NULL){
		printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(Q)){
		Q->front = Q->back = N;
	}
	else {
		Q->back->next = N;
		Q->back = N;
	}
	Q->numItems++;
}

// Dequeue
// deletes the element at the front of Q
// pre: !isEmpty(Q)
void Dequeue(Queue Q){
	Node N = NULL;
	if (Q == NULL){
		printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(Q)){
		printf("Queue Error: calling Dequeue() on empty Queue\n");
		exit(1);
	}

	N = Q->front;
	if (getLength(Q) > 1){
		Q->front = Q->front->next;
	}
	else {
		Q->front = Q->back = NULL;
	}
	Q->numItems--;
	freeNode(&N);
}


// Other functions

// printQueue()
// prints data elements in Q on a single line to stdout
void printQueue(Queue Q){
	Node N = NULL;
	if (Q == NULL){
		printf("Queue Error: calling printQueue() on NULL Queue reference\n");
		exit(1);
	}

	for (N = Q->front; N != NULL; N = N->next){
		printf("%d ", N->data);
	}
	printf("\n");
}

// equals()
// returns 1 (true) if A is identical to B, 0 (false) otherwise
int equals(Queue A, Queue B){
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL){
		printf("Queue Error: calling equals() on NULL Queue reference\n");
		exit(1);
	}

	eq = (A->numItems == B->numItems);
	N = A->front;
	M = B->front;
	while (eq && N != NULL){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}