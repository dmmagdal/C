// Dictionary.h
// Header file for the DictionaryADT

#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_

// Dictionary
// Exported reference type
typedef struct dictionaryObj* Dictionary;

// newDictionary()
// Constructor for the Dictionary type
Dictionary newDictionary(void);

// freeDictionary()
// Destructor for the Dictionary type
void freeDictionary(Dictionary* pD);

// isEmpty()
// returns 1 (true) if D  is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D);

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D);

// lookup()
// returns teh value v such that (k, v) is in D, or returns NULL
// if no such value v exists
// pre: none
char* lookup(Dictionary D, char* k);

// insert()
// inserts new (key, value) pair into D
// pre: lookup(D, k) == NULL
void insert(Dictionary D, char* k, char* v);

// delete()
// deletes pair with the key k
// pre: lookup(D, k) != NULL
void delete(Dictionary D, char* k);

// makeEmpty()
// resets D to the empty state
// pre: none
void makeEmpty(Dictionary D);

// printDictionary()
// prints a text representation of D to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D);


#endif