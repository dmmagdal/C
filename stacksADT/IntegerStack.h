// IntegerStack.h
// Header file for the IntegerStack ADT

#ifndef _INTEGER_STACK_H_INCLUDE_
#define _INTEGER_STACK_H_INCLUDE_

// Stack
// eported reference type
typedef struct stackObj* Stack;

// newStack()
// constructor for the Stack type
Stack newStack(void);

// freeStack()
// destructor for teh Stack type
void freeStack(Stack* pS);

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Stack S);

// push()
// pushes x onto the top of the stack
// pre: none
void push(Stack S, int x);

// pop()
// deletes and returns the top of the stack
// pre: !isEmpty()
int pop(Stack S);

// peek()
// reut
// pre: !isEmpty()
int peek(Stack S);

// popAll()
// empties the stack by popping
// pre: !isEmpty()
void popAll(Stack S);

// printStack()
// prints the stack to a file pointed to by out
// pre: none
void printStack(FILE* out, Stack S);

#endif