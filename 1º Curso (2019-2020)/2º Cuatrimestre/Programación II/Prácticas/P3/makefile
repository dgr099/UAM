.PHONY: clean
CC = gcc -g -ansi -Wall -pedantic
all: p3_e1 p3_e2
p3_e1:	p3_e1.o	node.o	graph.o	queue_fp.o
	$(CC)	-o$@	$^
p3_e1.o:	p3_e1.c	node.h	graph.h
	$(CC)	-c p3_e1.c
p3_e2:	p3_e2.o	node.o	graph.o	queue_fp.o
	$(CC)	-o$@	$^
p3_e2.o:	p3_e2.c	node.h	graph.h	types.h
	$(CC)	-c p3_e2.c	
graph.o:	graph.c	graph.h	node.h
	$(CC) -c graph.c
node.o:	node.c	node.h
	$(CC)	-c	node.c
queue_fp.o:	queue_fp.c	queue_fp.h
	$(CC)	-c	queue_fp.c

ej_examen: ej_examen.o	element.o	queue_fp.o
	$(CC) -o$@	$^
ej_examen.o:	ej_examen.c	types.h	queue_fp.h	element.h
	$(CC) -o$@ -c $<

element.o:	element.c	element.h
	$(CC) -o$@ -c $<

clean:
	rm *.o