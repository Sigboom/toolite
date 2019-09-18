Target = skipsList

CC = g++
Wall = -g -Wall
STD = -std=c++11

CC_ARGS = $(Wall) $(STD) -o

BASE_OBJ = baseList/list.o baseList/listNode.o baseList/skipNode.o
OBJ = skipsList.o

.PHONY:
	clean

$(Target): $(OBJ)
	$(CC) $(CC_ARGS) $(Target) $(BASE_OBJ) $(OBJ)

clean:
	-rm  $(OBJ) $(Target)
