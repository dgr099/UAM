.PHONY: remove
CC = gcc -g -Wall -pedantic -ansi
resultado: p1_e1.o	node.o
	$(CC) -o $@ $^
node.o:	node.h node.c
	$(CC) -c node.c
p1_e1.o: p1_e1.c	node.h
	$(CC) -c p1_e1.c
remove:
	rm *.o
