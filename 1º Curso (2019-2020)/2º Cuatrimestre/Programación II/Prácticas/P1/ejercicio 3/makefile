.PHONY: remove
CC = gcc -g -Wall -pedantic -ansi
resultado: p1_e3.o	node.o	graph.o
	$(CC) -o $@ $^
node.o:	node.h node.c
	$(CC) -c node.c
p1_e3.o: p1_e3.c	node.h	graph.h
	$(CC) -c p1_e3.c
graph.o:	graph.c	graph.h	node.h
	$(CC) -c graph.c
remove:
	rm *.o
