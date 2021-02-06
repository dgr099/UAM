.PHONY: clean
CC = gcc -g -ansi -Wall -pedantic
all: p3_e3 p3_e3_c
p3_e3:	p3_e3.o	node.o	graph.o	queue_fp.o
	$(CC)	-o$@	$^
p3_e3.o:	p3_e3.c	node.o	graph.o	queue_fp.o
	$(CC)	-c $<

p3_e3_c:	p3_e3_c.o	graph.o	node.o	libstack_fp.a
	$(CC)	-o$@	$^ -L.	-lstack_fp

p3_e3_c.o:	p3_e3_c.c	graph.o	node.o	libstack_fp.a
	$(CC)	-c $<	-I.
graph.o:	graph.c	graph.h	node.h
	$(CC) -c $<

queue_fp.o:	queue_fp.c	queue_fp.h
	$(CC)	-c	$<
stack.o:	stack.c	stack.h	element.h
	$(CC)	-c	$<
node.o: node.c node.h
	$(CC)	-c	$<
clean:
	rm *.o