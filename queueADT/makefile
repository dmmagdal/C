# makefile for dictionary ADT and its client

ADT_NAME	= Queue
SOURCES		= $(ADT_NAME).c $(ADT_NAME)Test.c
OBJECTS		= $(ADT_NAME).o $(ADT_NAME)Test.o
HEADERS		= $(ADT_NAME).h
EXEBIN		= $(ADT_NAME)Test
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
