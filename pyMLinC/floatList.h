// floatList.h
// author: Diego Magdaleno
// Header for floatList.c

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type
typedef struct floatListObj* floatList;


// Constructors-Destructors

// newList()
// returns reference to new empty list object
floatList newList(void);

// freeList()
// frees all heap memory associated with List *pL, and sets *pL to null
void freeList(floatList* pL);


// Access functions

// front()
// returns the value at the front of L
// pre: !isEmpty(L)
float front(floatList L);

// back()
// returns the value at the back of L
// pre: !isEmpty(L)
float back(floatList L);

// get()
// returns the value at the cursor of L
// pre: cursor != null
float get(floatList L);

// length()
// returns the length of L
int length(floatList L);

// index()
// returns the index at the cursor of L
// pre: cursor != null
int index(floatList L);

// equals()
// returns 1 (true) if A is identical to B, 0 (false) otherwise
// pre: none 
int equals(floatList A, floatList B);

// isEmpty()
// returns 1 (true) if L is empty, 0 (false) otherwise
// pre: none
// private
int isEmpty(floatList L);


// Manipulation procedures

// clear()
// resets List L to it's empty state
// pre: none
void clear(floatList L);

// moveFront()
// move the cursor to the front node of L
// pre: !isEmpty(L)
void moveFront(floatList L);

// moveBack()
// move the cursor to the back node of L
// pre: !isEmpty(L)
void moveBack(floatList L);

// movePrev()
// move the cursor to its previous pointer
// pre: !isEmpty(L)
void movePrev(floatList L);

// moveNext()
// move the cursor to its next pointer
// pre: !isEmpty(L)
void moveNext(floatList L);

// prepend()
// add a new node to the front of the List
// pre: none
void prepend(floatList L, float data);

// append()
// add a new node to the back of the List
// pre: none
void append(floatList L, float data);

// insertBefore()
// add a new node in the List in front of the cursor
// pre: cursor != null
void insertBefore(floatList L, float data);

// insertAfter()
// add a new node in the List in behind the cursor
// pre: cursor != null
void insertAfter(floatList L, float data);

// deleteFront()
// delete the front node of the List
// pre: !isEmpty(L)
void deleteFront(floatList L);

// deleteBack()
// delete the back node of the List
// pre: !isEmpty(L)
void deleteBack(floatList L);

// deleteItem()
// delete the item specified from the List
// pre: !isEmpty(L), data is in list
void deleteItem(floatList L, float data)

// delete
// deletes the node at the cursor in the List
// pre: cursor != null
void delete(floatList L);


// Other operations

// printList()
// prints data elements in List on single line to out
// pre: none
void printList(FILE* out, floatList L);

// copyList()
// returns an identical copy of the current list
// pre: none
floatList copyList(floatList L);

// concat()
// returns a new list composed of the concatenation of Lists A and B
// pre: none
floatList concat(floatList A, floatList B);

#endif
