CFLAGS=-g
LDFLAGS=-pthread 
CC=gcc
all: conc_cycle
conc_cycle:	conc_cycle.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

conc_cycle.o: conc_cycle.c
	$(CC) -c $(CFLAGS) $< -o $@