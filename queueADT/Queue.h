// Queue.h
// Header file for Queue ADT

#ifndef _QUEUE_H_INCLLUDE_
#define _QUEUE_H_INCLLUDE_

// Exported type
typedef struct QueueObj* Queue;


// Constructors-Destructors

// newQueue()
// returns reference to new empty queue object
Queue newQueue(void);

// freeQueue()
// frees all heap memory associated with Queue *pQ, and sets *pQ to null
void freeQueue(Queue* pQ);


// Access functions

// getFront()
// returns the value at the front of Q
// pre: !isEmpty(Q)
int getFront(Queue Q);

// getLength()
// returns the length of Q
int getLength(Queue Q);

// isEmpty()
// returns 1 (true) if Q is empty, otherwise returns 0 (false)
int isEmpty(Queue Q);


// Manipulation procedures

// Enqueue()
// places new data element at the end of Q
void Enqueue(Queue Q, int data);

// Dequeue
// deletes the element at the front of Q
// pre: !isEmpty(Q)
void Dequeue(Queue Q);


// Other functions

// printQueue()
// prints data elements in Q on a single line to stdout
void printQueue(Queue Q);

// equals()
// returns 1 (true) if A is identical to B, 0 (false) otherwise
int equals(Queue A, Queue B);

#endif