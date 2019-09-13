CC = g++

STD = -std=c++11

INCLUDE = 

Wall = -Wall

OBJ = listNode.o list.o skipListNode.o skipList.o

.PHONY:clean

skipList: $(OBJ) 
	$(CC) $(Wall) $(STD) -o skipList $(OBJ)

skipListNode.o: skipListNode.cpp skipListNode.h
	$(CC) $(Wall) $(STD) -c -o skipListNode.o skipListNode.cpp

skipList.o: skipList.cpp list.h skipListNode.o
	$(CC) $(Wall) $(STD) -c -o skipList.o skipList.cpp

listNode.o: listNode.cpp listNode.h
	$(CC) $(Wall) $(STD) -c -o listNode.o listNode.cpp

list.o: list.cpp list.h listNode.o
	$(CC) $(Wall) $(STD) -c -o list.o list.cpp

clean:
	rm *.o skipList
