// floatList.c
// author: Diego Magdaleno
// Linked list of floats implementation of List ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

// structs

// private NodeObj type
typedef struct NodeObj{
	float data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct floatListObj{
	Node front;
	Node back;
	Node cursor;
	int numItems;
	int index;
} floatListObj;


// Constructors-Destructors

// newNode()
// returns reference to new Node object. Initializes next and data fields
// Private 
Node newNode(float data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
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

// newList()
// returns reference to new empty list object
floatList newList(void){
	floatList L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->numItems = 0;
	L->index = -1;
	return(L);
}

// freeList()
// frees all heap memory associated with List *pL, and sets *pL to null
void freeList(floatList* pL){
	if (pL != NULL && *pL != NULL){
		while (!isEmpty(*pL)){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}


// Access functions

// front()
// returns the value at the front of L
// pre: !isEmpty(L)
int front(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling front() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling front() on empty List\n");
		exit(1);
	}
	return(L->front->data);
}

// back()
// returns the value at the back of L
// pre: !isEmpty(L)
int back(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling back() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling back() on empty List\n");
		exit(1);
	}
	return(L->back->data);
}

// get()
// returns the value at the cursor of L
// pre: cursor != null
float get(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling cursor() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
		fprintf(stderr, "List Error: Calling cursor() on NULL List cursor\n");
		exit(1);
	}
	return(L->cursor->data);
}

// length()
// returns the length of L
int length(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->numItems);
}

// index()
// returns the index at the cursor of L
// pre: cursor != null
int index(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

// equals()
// returns 1 (true) if A is identical to B, 0 (false) otherwise
// pre: none 
int equals(floatList A, floatList B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: Calling equals() on NULL List reference\n");
		exit(1);
	}
	int eq = (A->numItems == B->numItems);
	Node N = A->front;
	Node M = B->front;
	while (eq && N != NULL){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return(eq);
}

// isEmpty()
// returns 1 (true) if L is empty, 0 (false) otherwise
// pre: none
// private
int isEmpty(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(L->numItems == 0);
}


// Manipulation procedures

// clear()
// resets List L to it's empty state
// pre: none
void clear(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling clear() on NULL List reference\n");
		exit(1);
	}
	while (!isEmpty(L)){
		deleteFront(L);
	}
}

// moveFront()
// move the cursor to the front node of L
// pre: !isEmpty(L)
void moveFront(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling moveFront() on empty list\n");
		exit(1);
	}
	L->cursor = L->front;
	L->index = 0;	
}

// moveBack()
// move the cursor to the back node of L
// pre: !isEmpty(L)
void moveBack(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling moveBack() on empty list\n");
		exit(1);
	}
	L->cursor = L->back;
	L->index = L->numItems-1;	
}

// movePrev()
// move the cursor to its previous pointer
// pre: !isEmpty(L)
void movePrev(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor != NULL && L->cursor != L->front){
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if (L->cursor != NULL && L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	// otherwise, the cursor is null, so do nothing
}

// moveNext()
// move the cursor to its next pointer
// pre: !isEmpty(L)
void moveNext(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor != NULL && L->cursor != L->back){
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if (L->cursor != NULL && L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}
	// otherwise, the cursor is null, so do nothing
}

// prepend()
// add a new node to the front of the List
// pre: none
void prepend(floatList L, float data){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling prepend() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data);
	if (isEmpty(L)){
		L->front = L->back = N;
	}
	else{
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->numItems++;
}

// append()
// add a new node to the back of the List
// pre: none
void append(floatList L, float data){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling append() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data);
	if (isEmpty(L)){
		L->front = L->back = N;
	}
	else{
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->numItems++;
}

// insertBefore()
// add a new node in the List in front of the cursor
// pre: cursor != null
void insertBefore(floatList L, float data){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
		fprintf(stderr, "List Error: Calling insertBefore() on NULL cursor\n");
		exit(1);
	}
	Node N = newNode(data);
	N->prev = L->cursor->prev;
	N->next = L->cursor;
	if (L->cursor == L->front){
		L->front = N;
	}
	else {
		L->cursor->prev->next = N;
	}
	L->cursor->prev = N;
	L->index++;
	L->numItems++;
}

// insertAfter()
// add a new node in the List in behind the cursor
// pre: cursor != null
void insertAfter(floatList L, float data){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
		fprintf(stderr, "List Error: Calling insertBefore() on NULL cursor\n");
		exit(1);
	}
	Node N = newNode(data);
	N->next = L->cursor->next;
	N->prev = L->cursor;
	if (L->cursor == L->back){
		L->back = N;
	}
	else {
		L->cursor->next->prev = N;
	}
	L->cursor->next = N;
	L->numItems++;
}

// deleteFront()
// delete the front node of the List
// pre: !isEmpty(L)
void deleteFront(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling deleteFront() on empty list\n");
		exit(1);
	}
	if (L->cursor == L->front && L->numItems == 1){
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->cursor == L->front && L->numItems > 1){
		moveNext(L);
		L->index = 0;
	}
	Node N = L->front;
	L->front = L->front->next;
	L->numItems--;
	freeNode(&N);
}

// deleteBack()
// delete the back node of the List
// pre: !isEmpty(L)
void deleteBack(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling deleteBack() on empty list\n");
		exit(1);
	}
	if (L->cursor == L->back && L->numItems == 1){
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->cursor == L->back && L->numItems > 1){
		movePrev(L);
		L->index = L->numItems-1;
	}
	Node N = L->back;
	L->back = L->back->prev;
	L->numItems--;
	freeNode(&N);
}

// deleteItem()
// delete the item specified from the List. Removes the first instance of said item
// pre: !isEmpty(L), data is in list
void deleteItem(floatList L, float data){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if (isEmpty(L)){
		fprintf(stderr, "List Error: Calling deleteBack() on empty list\n");
		exit(1);
	}
	int found = 0;
	moveFront(L);
	while (L->cursor != NULL && found == 0){
		if (L->cursor->data == data){
			found = 1;
			if (L->cursor == L->front && numItems == 1){
				deleteFront(L);
			}
			else if (L->cursor == L->front && numItems > 1){
				deleteFront(L);
			}
			else if (L->cursor == L->back && numItems > 1){
				deleteBack(L);
			}
			else{
				Node N = L->cursor;
				L->cursor = NULL;
				L->index = -1;
				N->prev->next = N->next;
				N->next->prev = N->prev;
				L->numItems--;
				freeNode(&N);
			}
		}
		else{
			moveNext(L);
		}
	}
}

// delete
// deletes the node at the cursor in the List
// pre: cursor != null
void delete(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling delete() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
		fprintf(stderr, "List Error: Calling delete() on NULL cursor\n");
		exit(1);
	}
	if (L->cursor == L->front){
		deleteFront(L);
	}
	else if  (L->cursor == L->back){
		deleteBack(L);
	}
	else {
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&N);
		L->numItems--;
		L->index = -1;
	}
}


// Other operations

// printList()
// prints data elements in List on single line to out
// pre: none
void printList(FILE* out, floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling printList() on NULL List reference\n");
		exit(1);
	}
	Node N = NULL;
	for (N = L->front; N != NULL; N = N->next){
		printf("%d ", N->data);
	}
}

// copyList()
// returns an identical copy of the current list
// pre: none
floatList copyList(floatList L){
	if (L == NULL){
		fprintf(stderr, "List Error: Calling copy() on NULL List reference\n");
		exit(1);
	}
	List M = newList();
	Node N = NULL;
	for (N = L->front; N != NULL; N = N->next){
		append(M, N->data);
	}
	return(M);
}

// concat()
// returns a new list composed of the concatenation of Lists A and B
// pre: none
floatList concat(floatList A, floatList B){
	if (A == NULL || B == NULL){
		fprintf(stderr, "List Error: Calling concat() on NULL List reference\n");
		exit(1);
	}
	moveFront(B);
	while (B->cursor != B->back){
		append(A, get(B));
		moveNext(B);
	}
	append(A, back(B));
	return(A);
}