.PHONY: clean clean_test

CFLAGS = -Wall -pedantic -g
CC = gcc
C = ./src/
H = ./include/
O = ./obj/


resultado:	$(O)command.o	$(O)dice.o	$(O)game_loop.o	$(O)game_reader.o	$(O)game.o $(O)graphic_engine.o	$(O)object.o	$(O)player.o	$(O)screen.o	$(O)set.o $(O)space.o	$(O)inventory.o	$(O)link.o
	$(CC)	-o $@ $^

test: dice_test space_test object_test inventory_test link_test player_test set_test	command_test

$(O)command.o:	$(C)command.c	$(H)command.h	$(H)game_reader.h	$(H)types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(O)command_test.o: $(C)command_test.c $(H)command_test.h	$(H)test.h	$(H)command.h	$(H)types.h 
	$(CC) $(CFLAGS) -c $< -o $@

command_test:	$(O)command_test.o	$(O)command.o
	$(CC) -o $@	$^

$(O)dice_test.o:	$(C)dice_test.c	$(H)dice.h	$(H)types.h $(H)test.h $(H)dice_test.h
	$(CC)	$(CFLAGS)	-c $< -o $@

dice_test:	$(O)dice_test.o	$(O)dice.o
	$(CC) -o $@	$^

$(O)dice.o:	$(C)dice.c	$(H)dice.h	$(H)types.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)game_loop.o:	$(C)game_loop.c	$(H)graphic_engine.h	$(H)game.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)game_reader.o:	$(C)game_reader.c	$(H)game.h	$(H)game_reader.h	$(H)object.h	$(H)space.h	$(H)player.h	$(H)link.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)game.o:	$(C)game.c	$(H)game.h	$(H)space.h	$(H)game_reader.h	$(H)player.h	$(H)object.h	$(H)inventory.h	$(H)link.h $(H)command.h	$(H)space.h	$(H)player.h	$(H)object.h	$(H)dice.h	$(H)link.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)graphic_engine.o:	$(C)graphic_engine.c	$(H)screen.h	$(H)graphic_engine.h $(H)command.h	$(H)player.h	$(H)object.h	$(H)dice.h	$(H)game_reader.h $(H)set.h	$(H)game.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)inventory_test.o:	$(C)inventory_test.c	$(H)inventory.h	$(H)object.h 	$(H)set.h	$(H)object.h $(H)test.h $(H)inventory_test.h
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

inventory_test:	$(O)inventory_test.o	$(O)inventory.o	$(O)set.o	$(O)object.o
	$(CC)	-o$@	$^

$(O)inventory.o:	$(C)inventory.c	$(H)inventory.h	$(H)types.h	$(H)set.h	$(H)object.h
	$(CC)	$(CFLAGS)	-c $< -o $@

$(O)link_test.o:	$(C)link_test.c	$(H)link.h	$(H)types.h $(H)test.h	$(H)link_test.h
	$(CC)	$(CFLAGS) -c $< -o $@

link_test:	$(O)link_test.o	$(O)link.o
	$(CC)	-o $@ $^

$(O)link.o:	$(C)link.c	$(H)link.h	$(H)types.h
	$(CC)	$(CFLAGS)	-c $<	 -o $@	

$(O)object.o:	$(C)object.c	$(H)types.h	$(H)object.h
	$(CC)	$(CFLAGS)	-c $<	-o	$@

$(O)object_test.o:	$(C)object_test.c	$(H)object.h	$(H)types.h $(H)test.h	$(H)object_test.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

object_test:	$(O)object_test.o	$(O)object.o
	$(CC)	$(CFLAGS)	-o$@	$^

$(O)player_test.o:	$(C)player_test.c	$(H)player.h	$(H)object.h	$(H)types.h	$(H)inventory.h	$(H)set.h	$(H)player_test.h	$(H)test.h
	$(CC)	$(CFLAGS) -c $< -o $@

player_test:	$(O)player_test.o	$(O)player.o	$(O)object.o	$(O)inventory.o	$(O)set.o
	$(CC)	-o $@	$^

$(O)player.o:	$(C)player.c	$(H)types.h	$(H)player.h	$(H)inventory.h	$(H)game.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

$(O)screen.o:	$(C)screen.c	$(H)screen.h
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

$(O)set_test.o:	$(C)set_test.c $(H)set.h	$(H)test.h	$(H)set_test.h
	$(CC)	$(CFLAGS)	-c $< -o $@

set_test:	$(O)set.o	$(O)set_test.o
	$(CC) $(CFLAGS)	$^ -o $@

$(O)space_test.o:	$(C)space_test.c	$(H)space.h	$(H)space_test.h	$(H)test.h	$(H)space_test.h
	$(CC)	$(CFLAGS)	-c	$< -o $@

space_test:	$(O)space_test.o $(O)space.o $(O)set.o
	$(CC) $(CFLAGS) $^ -o $@

$(O)set.o:	$(C)set.c	$(H)types.h	$(H)set.h
	$(CC)	$(CFLAGS)	-c	$<	-o $@

$(O)space.o:	$(C)space.c	$(H)types.h	$(H)space.h	$(H)game.h	$(H)set.h
	$(CC)	$(CFLAGS)	-c $< -o $@

				
clean:
	@echo "cleaning objects :-) and executable"
	rm $(O)*.o
	rm resultado

clean_test:
	@echo "cleaning test objects and test executables :-)"
	rm $(O)*test.o
	rm *test