CC = gcc
CFLAGS = -g -ansi -pedantic
CLIBS = -pthread

all: shell
shell: proc_shell.o
	$(CC) $(CFLAGS) $(CLIBS) -o shell $^
proc_shell.o: proc_shell.c
	$(CC) -c $^

clean: 
	rm proc_shell.o shell
