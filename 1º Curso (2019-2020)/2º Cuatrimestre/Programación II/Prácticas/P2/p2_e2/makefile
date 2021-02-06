CC = gcc -g -Wall	-pedantic -ansi
.PHONY:	remove
p2_e2:	p2_e2.o
	$(CC) -o$@ $^	-L.	-lstack_fp
p2_e2.o:	p2_e2.c	stack_fp.h	stack_types.h	types.h
	$(CC)	-c	p2_e2.c	-I.