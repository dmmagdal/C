// List.h
// Header file for List ADT


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type
typedef struct ListObj* List;


// Constructors-Destructors

// newList()
// returns reference to new empty list object
List newList(void);

// freeList()
// frees all heap memory associated with List *pL, and sets *pL to null
void freeList(List* pL);


// Access functions

// front()
// returns the value at the front of L
// pre: !isEmpty(L)
int front(List L);

// back()
// returns the value at the back of L
// pre: !isEmpty(L)
int back(List L);

// get()
// returns the value at the cursor of L
// pre: cursor != null
int get(List L);

// length()
// returns the length of L
int length(List L);

// index()
// returns the index at the cursro of L
// pre: cursor != null
int index(List L);

// equals()
// returns 1 (true) if A is identical to B, 0 (false) otherwise
// pre: none 
int equals(List A, List B);

// isEmpty()
// returns 1 (true) if L is empty, 0 (false) otherwise
// pre: none
// private
int isEmpty(List L);


// Manipulation procedures

// clear()
// resets List L to it's empty state
// pre: none
void clear(List L);

// moveFront()
// move the cursor to the front node of L
// pre: !isEmpty(L)
void moveFront(List L);

// moveBack()
// move the cursor to the back node of L
// pre: !isEmpty(L)
void moveBack(List L);

// movePrev()
// move the cursor to its previous pointer
// pre: !isEmpty(L)
void movePrev(List L);

// moveNext()
// move the cursor to its next pointer
// pre: !isEmpty(L)
void moveNext(List L);

// prepend()
// add a new node to the front of the List
// pre: none
void prepend(List L, int data);

// append()
// add a new node to the back of the List
// pre: none
void append(List L, int data);

// insertBefore()
// add a new node in the List in front of the cursor
// pre: cursor != null
void insertBefore(List L, int data);

// insertAfter()
// add a new node in the List in behind the cursor
// pre: cursor != null
void insertAfter(List L, int data);

// deleteFront()
// delete the front node of the List
// pre: !isEmpty(L)
void deleteFront(List L);

// deleteBack()
// delete the back node of the List
// pre: !isEmpty(L)
void deleteBack(List L);

// delete
// deletes the node at the cursor in the List
// pre: cursor != null
void delete(List L);


// Other operations

// printList()
// prints data elements in List on single line to out
// pre: none
void printList(FILE* out, List L);

// copyList()
// returns an identical copy of the current list
// pre: none
List copyList(List L);

// concat()
// returns a new list composed of the concatenation of Lists A and B
// pre: none
List concat(List A, List B);

#endif