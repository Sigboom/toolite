Target = skipList

CC = g++
STD = --std=c++11
Wall = -g -Wall

CC_ARGS = $(STD) $(Wall) -o

INCLUDE = 

BASE_OBJ = listNode.o list.o

OBJ = skipNode.o skipList.o

.PHONY:clean

$(Target): $(OBJ) 
	$(CC) $(CC_ARGS) $(Target) $(BASE_OBJ) $(OBJ)

list: listNode.o
	$(CC) -DDEBUG $(CC_ARGS) list list.cpp listNode.o

cleanlist:
	-rm $(BASE_OBJ) list

clean:
	-rm $(BASE_OBJ) $(OBJ) $(Target)
