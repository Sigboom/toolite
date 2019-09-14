CC = g++

CFLAGS_WARN = -g -Wall

std = -std=c++11

Include=

.PHONY:
	clean

skips_list: list.o skips_list.o
	$(CC) $(std) $(CFLAGE_WARN) -o skips_list list.o skips_list.o

list.o: base_list/list.cpp base_list/list.h
	$(CC) $(std) $(CFLAGE_WARN) -c -o list.o base_list/list.cpp

skips_list.o: skips_list.cpp skips_list.h
	$(CC) $(std) $(CFLAGE_WARN) -c -o skips_list.o skips_list.cpp

clean:
	rm *.o skips_list
