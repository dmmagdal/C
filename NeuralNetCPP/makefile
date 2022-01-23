# makefile for neural net and its training data

NN_NAME			= neural-net
NN_SOURCES		= $(NN_NAME).cpp
TRAIN_NAME		= make-training-data
TRAIN_SOURCES	= $(TRAIN_NAME).cpp
NN_EXEBIN		= neural-net
TRAIN_EXEBIN	= make-training-data

all: $(NN_EXEBIN) $(TRAIN_EXEBIN)

$(NN_EXEBIN) : 
	g++ $(NN_SOURCES) -o $(NN_EXEBIN)

$(TRAIN_EXEBIN) : 
	g++ $(TRAIN_SOURCES) -o $(TRAIN_EXEBIN)

clean:
	rm -f $(NN_EXEBIN) $(TRAIN_EXEBIN)
