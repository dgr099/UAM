main_list : main_list.o int.o
	gcc -g -no-pie -o main_list main_list.o int.o -L. -llist-linux

main_list.o : main_list.c int.h	int.c
	gcc -g -c -Wall -ansi main_list.c

int.o:	int.c	int.h	types.h
	gcc -c int.c

clean :
	rm main_list main_list.o

