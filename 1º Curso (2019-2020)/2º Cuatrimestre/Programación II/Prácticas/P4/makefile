.PHONY:	remove

cc	=	gcc 
CFLAGS = -g -Wall -pedantic -ansi
all: p4_e1 p4_e2 p4_e2_option1 p4_e2_option2 p4_e3_a p4_e3_b

p4_e1:	p4_e1.o
	$(CC) $(CFLAGS) $^ -L. -llist -L. -lstack_fp -o $@

p4_e1.o:	p4_e1.c	types.h	list.h	stack_types.h
	$(CC) $(CFLAGS) -c $< -o $@ -I.



p4_e2: p4_e2.o	node.o	graph_list.o queue_fp.o
	$(CC) $(CFLAGS) $^ -o $@ -L. -llist 

p4_e2.o: p4_e2.c	graph_list.h queue_fp.h
	$(CC) $(CFLAGS) -c $< -o $@ -I.

p4_e2_option1: p4_e2_option1.o	graph_option1.o	node.o	queue_fp.o
	$(CC) $(CFLAGS) $^ -o $@ -L. -llist -L. -lstack_fp

p4_e2_option1.o:	p4_e2_option1.c	graph_option1.h	queue_fp.h
	$(CC) $(CFLAGS) -c $< -o $@ -I.

p4_e2_option2: p4_e2_option2.o	graph_option2.o	node.o	queue_fp.o
	$(CC) $(CFLAGS) $^ -o $@ -L. -llist -L. -lstack_fp

p4_e2_option2.o:	p4_e2_option2.c	graph_option2.h	queue_fp.h
	$(CC) $(CFLAGS) -c $< -o $@ -I.


p4_e3_a:	p4_e3_a.o	tree.o		graph.o		node.o
	$(CC)	$(CFLAGS) -o$@	$^

p4_e3_a.o:	p4_e3_a.c	tree.h		graph.h
	$(CC)	$(CFLAGS) -o$@ -c $<

p4_e3_b:	p4_e3_b.o tree.o
	$(CC) $(CFLAGS) $^ -L. -llist -L. -lstack_fp -o $@

p4_e3_b.o:	p4_e3_b.c	types.h	list.h	stack_types.h	tree.h
	$(CC) $(CFLAGS) -c $< -o $@ -I.

tree.o:		tree.c		tree.h		types.h		node.h
	$(CC)	$(CFLAGS) -c tree.c
	
graph.o:	graph.c graph.h	node.h
	$(CC) $(CFLAGS) -o $@ -c $<

node.o:	node.c	node.h	
	$(CC) $(CFLAGS) -c $< -o $@

graph_list.o:	graph_list.c	graph_list.h	list.h	node.h
	$(CC) $(CFLAGS) -c $<  -I. -o $@

graph_option1.o:	graph_option1.c	graph_option1.h	list.h
	$(CC)	$(CFLAGS) -c $< -I. -o $@

graph_option2.o:	graph_option2.c	graph_option2.h	list.h
	$(CC)	$(CFLAGS) -c $< -I. -o $@

queue_fp.o:	queue_fp.c	queue_fp.h
	$(CC) $(CFLAGS) -c $< -o $@

remove:
	rm *.o
