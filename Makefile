# Makefile for List class

# the compiler and linker are specified below
CC = g++
LD = g++

# these are options for the compiler and linker
# the -c instructs the compiler to just compile (to a .o) and not link
CFLAGS = -g -Wall -c
LDFLAGS = -g

all: EnterTheLists

#List.o: List.cpp List.h
#	$(CC) $(CFLAGS) List.cpp

test_list.o: test_list.cpp List.h #List.cpp
	$(CC) $(CFLAGS) test_list.cpp

test_list: test_list.o #List.o
	$(LD) $(LDFLAGS) -o test_list test_list.o #List.o

EnterTheLists.o: EnterTheLists.cpp List.h #List.cpp
	$(CC) $(CFLAGS) EnterTheLists.cpp

EnterTheLists: EnterTheLists.o  test_list.o#List.o
	$(LD) $(LDFLAGS) -o EnterTheLists EnterTheLists.o #List.o
	$(LD) $(LDFLAGS) -o test_list test_list.o
clean:
	rm *.o
