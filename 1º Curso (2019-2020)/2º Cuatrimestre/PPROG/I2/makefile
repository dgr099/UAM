.PHONY: remove test_remove

CFLAGS = -Wall -pedantic -g
CC = gcc

resultado:	command.o	game_loop.o	game_reader.o	game.o	graphic_engine.o	object.o	player.o	screen.o	space.o	set.o	dice.o
	$(CC) -g -o $@ $^	

test: dice_test set_test

command.o:	command.c	command.h	game_reader.h
	$(CC) $(CFLAGS) -c command.c

game_loop.o:	game_loop.c	graphic_engine.h
	$(CC) $(FLAGS) -c game_loop.c

game_reader.o:	game_reader.c	game_reader.h	game.h	object.h	space.h
	$(CC) $(CFLAGS) -c game_reader.c

game.o:	game.c	game.h	game_reader.h	player.h	object.h	space.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o:	graphic_engine.c	screen.h	graphic_engine.h	command.h	player.h	object.h	dice.h	game_reader.h	set.h
	$(CC) $(CFLAGS) -c graphic_engine.c

object.o:	object.c	types.h	object.h
	$(CC) $(CFLAGS) -c object.c

player.o:	player.c	types.h	player.h
	$(CC) $(CFLAGS) -c player.c

screen.o:	screen.c	screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o:	space.c	space.h	types.h	game.h	set.h
	$(CC) $(CFLAGS) -c space.c

set.o:	set.c	set.h	types.h
	$(CC) $(CFLAGS) -c set.c

set_test.o: set_test.c set.h
	$(CC) $(CFLAGS) -c set_test.c

set_test:	set_test.o	set.o
	$(CC) -o$@ $^ 

dice.o:	dice.c	dice.h	types.h
	$(CC) $(CFLAGS) -c dice.c

dice_test.o:	dice_test.c	dice.h
	$(CC) $(CFLAGS) -c dice_test.c

dice_test:	dice_test.o	dice.o
	$(CC) -o$@ $^

remove:
	@echo "removing objects and executable:-)"
	rm *.o
	rm resultado
test_remove:
	@echo "removing only objects and executable test :-)"
	rm *test.o
	rm *test