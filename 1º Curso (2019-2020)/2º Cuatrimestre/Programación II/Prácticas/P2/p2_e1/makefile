.PHONY:	remove
CC = gcc	-g	-Wall	-pedantic	-ansi
p2_e1:	p2_e1.o
	$(CC)	-o$@	$^	-L.	-lstack_fp
p2_e1.o:	p2_e1.c	stack_fp.h	stack_types.h	types.h
	$(CC)	-g	-c	p2_e1.c	-I.
remove:
	rm *.o