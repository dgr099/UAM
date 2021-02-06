CC = gcc -g -Wall	-pedantic -ansi
.PHONY:	remove

all:	p2_e3_b p2_e3_a	p2_e2	p2_e1	p2_e0_a	p2_e0_b 
p2_e3_b:	stack.o	element.o	p2_e3_b.o
	$(CC)	-o $@ $^
p2_e3_b.o:	p2_e3_b.c	element.c	stack.c
	$(CC) -c p2_e3_b.c

p2_e3_a:	stack.o	element.o	p2_e3_a.o
	$(CC)	-o $@ $^
p2_e3_a.o:	p2_e3_a.c	element.c	stack.c
	$(CC) -c p2_e3_a.c

p2_e2:	p2_e2.o
	$(CC) -o$@ $^	-L.	-lstack_fp
p2_e2.o:	p2_e2.c	stack_fp.h	stack_types.h	types.h
	$(CC)	-c	p2_e2.c	-I.

p2_e1:	p2_e1.o
	$(CC)	-o$@	$^	-L.	-lstack_fp
p2_e1.o:	p2_e1.c	stack_fp.h	stack_types.h	types.h
	$(CC)	-g	-c	p2_e1.c	-I.

p2_e0_b:	p2_e0_b.o	node.o
	$(CC) $^ -L.	-lstack_fp -o $@
p2_e0_b.o:	p2_e0_b.c	stack_fp.h	stack_types.h
	$(CC) -c p2_e0_b.c -I.

p2_e0_a:	p2_e0_a.o
	$(CC) $^ -L. -lstack_fp -o $@
p2_e0_a.o:	p2_e0_a.c	stack_fp.h	stack_types.h
	$(CC) -c -o p2_e0_a.o p2_e0_a.c -I.

node.o:	node.c	node.h
	$(CC)	-c	node.c

stack.o:	stack.c	stack.h	types.h
	$(CC)	-c	stack.c

element.o:	element.c	element.h	types.h
	$(CC) -c	element.c

remove:
	@echo "removing objects :-)"
	rm *.o

