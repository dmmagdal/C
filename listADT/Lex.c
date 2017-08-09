// Lex.c
// Diego Magdaleno
// dmmagdal
// pa2: Sorts strings in a file using list ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 100

int main(int argc, char *argv[])
{
	// check command line for correct number of arguments
	if (argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file> \n", argv[0]);
		exit(EXIT_FAILURE);
	}


	int lineCount = 0;								// hold linecount variables
	FILE *in, *out;									// pointers to input and output files
	List indexList = newList();						// create new list to store the indices
	char line[MAX_LEN];								// hold the string of each line
	char* lineinput[MAX_LEN];						// holds all the input from each line of the file


	// open files for reading and writing
	in = fopen(argv[1], "r");						// open input file to read
	out = fopen(argv[2], "w");						// open output file to write to
	if (in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	// count the lines and store each line to the array
	while (fgets(line, MAX_LEN, in) != NULL){
		lineinput[lineCount] = strdup(strtok(line, "\n"));
		// printf("%s\n", lineinput[lineCount]);	// test storage of line to array
		lineCount++;
	}


	// copy array to smaller sized array
	char* input[lineCount];
	for (int i = 0; i < lineCount; i++){
		input[i] = lineinput[i];
		// printf("%s\n", input[i]);				// test if array copied correctly
	}

	// sorting algorithm
	append(indexList, 0);
	for (int i = 1; i < lineCount; i++){
		moveFront(indexList);
		if (strcmp(input[i], input[get(indexList)]) < 0){
			insertBefore(indexList, i);
		}
		else {
			while (strcmp(input[i], input[get(indexList)]) > 0){
				if (get(indexList) == back(indexList)){
					insertAfter(indexList, i);
				}
				else {
					moveNext(indexList);
				}
			}
			insertBefore(indexList, i);
		}
	}

	// print to file 
	moveFront(indexList);
	while (index(indexList) != length(indexList)-1){
		fprintf(out, "%s\n", input[get(indexList)]);
		// printf("%s\n", input[get(indexList)]);	// test if sort worked correctly
		moveNext(indexList);
	}



	// clean up te memory
	clear(indexList);
	freeList(&indexList);
	fclose(in);
	fclose(out);

	exit(EXIT_SUCCESS);
} 