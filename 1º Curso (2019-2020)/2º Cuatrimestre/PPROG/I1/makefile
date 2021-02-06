.PHONY: remove

CC = gcc
CFLAS = -g -Wall -pedantic

resultado:	command.o	game_loop.o	game_reader.o	game.o	graphic_engine.o	object.o	player.o	screen.o	space.o
	$(CC) $(CFLAGS) -o $@ $^	

command.o:	command.c	command.h
	$(CC) $(CFLAGS) -c command.c

game_loop.o:	game_loop.c	graphic_engine.h	game.h	command.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o:	game_reader.c	game_reader.h	game.h
	$(CC) $(CFLAGS) -c game_reader.c

game.o:	game.c	game.h	game_reader.h	player.h	object.h	space.h	types.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o:	graphic_engine.c	screen.h	command.h	player.h	object.h	game_reader.h
	$(CC) $(CFLAGS) -c graphic_engine.c

object.o:	object.c	types.h	object.h
	$(CC) $(CFLAGS) -c object.c

player.o:	player.c	types.h	player.h
	$(CC) $(CFLAGS) -c player.c

screen.o:	screen.c	screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o:	space.c	space.h	types.h
	$(CC) $(CFLAGS) -c space.c

remove:
	rm *.o