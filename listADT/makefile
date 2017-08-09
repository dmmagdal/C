# makefile for dictionary ADT and its client

ADT_NAME	= List
SOURCES		= $(ADT_NAME).c Lex.c
OBJECTS		= $(ADT_NAME).o Lex.o
HEADERS		= $(ADT_NAME).h
EXEBIN		= Lex
FLAGS		= -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean:
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN)
