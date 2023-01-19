CC=gcc
CFLAGS=-Wall -g

all: main

main: main.o graph.o
	gcc main.c graph.o -o prog

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c
clean:
	rm -f *.o prog