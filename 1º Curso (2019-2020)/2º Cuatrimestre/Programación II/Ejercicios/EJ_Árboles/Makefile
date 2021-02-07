CC=gcc
CFLAGS=-Wall -g
CFLAGSOPT=-O2
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-ltree

all: test_tree

test_tree: test_tree.c file_utils.c elements.c libtree.a
	$(CC) -o test_tree $(CFLAGS) test_tree.c file_utils.c elements.c $(LDFLAGS) $(LDLIBS)
clean:
	rm  -f test_tree
