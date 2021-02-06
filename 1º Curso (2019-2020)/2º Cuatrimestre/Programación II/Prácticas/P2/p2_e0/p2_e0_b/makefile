
CC	=	gcc	-g	-Wall	-pedantic	-ansi

resultado:	p1_e2_b.o	node.o
	$(CC) $^ -L.	-lstack_fp -o $@

p1_e2_b.o:	p1_e2_b.c	stack_fp.h	stack_types.h
	$(CC) -c p1_e2_b.c -I.

node.o:	node.c	node.h
	$(CC)	-c	node.c
remove:
	rm	*.o