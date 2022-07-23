.PHONY: clean
CFLAGS = -Wall -pedantic -fno-stack-protector -g
CC = gcc
C = src/
H = include/
O = obj/
L = lib/

all: obj server client
	unzip -n archivos_media.zip

obj:
	mkdir obj

server: $(O)server.o $(O)picohttpparser.o $(L)libutils.a
	$(CC) $(CFLAGS)	$^ -o $@ -pthread -L$(L) -lutils

client: $(O)client.o
	$(CC) $(CFLAGS)	$^ -o $@ -pthread

$(O)server.o: $(C)server.c
	$(CC) $(CFLAGS) -c $< -o $@

$(O)client.o: $(C)client.c
	$(CC) $(CFLAGS) -c $< -o $@

$(O)picohttpparser.o: $(C)picohttpparser.c
	$(CC) $(CFLAGS) -c $< -o $@

$(O)utils.o: $(C)utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(L)libutils.a: $(O)utils.o
	ar -rcs $@ $<


clean:
	@echo "cleaning"
	rm $(O)*.o client server
