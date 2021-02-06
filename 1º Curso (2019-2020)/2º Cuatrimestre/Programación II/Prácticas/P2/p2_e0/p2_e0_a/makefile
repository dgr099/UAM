.PHONY:	remove

cc	=	gcc	-g	-Wall	-pedantic	-ansi

p2_e0_a:	p2_e0_a.o
	$(CC) $^ -L. -lstack_fp -o $@

p2_e0_a.o:	p2_e0_a.c	stack_fp.h	stack_types.h
	$(CC) -c -o p2_e0_a.o p2_e0_a.c -I.

remove:
	rm *.o
