CC = g++

STD = -std=c++11

INCLUDE = 

Wall = 

.PHONY:clean

skip_list: list.o skip_list.o
	$(CC) $(STD) -o skip_list list.o skip_list.o 

skip_list.o: skip_list.cpp list.h
	$(CC) -c $(STD) -o skip_list.o skip_list.cpp

list.o: list.cpp list.h
	$(CC) -c $(STD) -o list.o list.cpp 

clean:
	rm list.o skip_list.o skip_list
