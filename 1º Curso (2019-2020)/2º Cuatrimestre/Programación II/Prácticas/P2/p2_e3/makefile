CC = gcc -g -Wall	-pedantic -ansi
.PHONY:	remove

p2_e3_a:	stack.o	element.o	p2_e3_a.o
	$(CC)	-o $@ $^

p2_e3_a.o:	p2_e3_a.c	element.c	stack.c
	$(CC) -c p2_e3_a.c
stack.o:	stack.c	stack.h	types.h
	$(CC)	-c	stack.c

element.o:	element.c	element.h	types.h
	$(CC) -c	element.c

p2_e3_b:	stack.o	element.o	p2_e3_b.o
	$(CC)	-o $@ $^

p2_e3_b.o:	p2_e3_b.c	element.c	stack.c
	$(CC) -c p2_e3_b.c

remove:
	rm *.o

