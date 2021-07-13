CC = gcc
CFLAGS = -g 
CLIBS = -lrt -lpthread

all: stream

stream: stream-ui.o stream-server.o stream-client.o
	$(CC) $(CFLAGS) -o stream-ui stream-ui.o $(CLIBS)
	$(CC) $(CFLAGS) -o stream-server stream-server.o $(CLIBS)
	$(CC) $(CFLAGS) -o stream-client stream-client.o $(CLIBS)

stream-ui.o: stream-ui.c
	$(CC) $(CFLAGS) -c $^

stream-server.o: stream-server.c
	$(CC) $(CFLAGS) -c $^

stream-client.o: stream-client.c
	$(CC) $(CFLAGS) -c $^


exe: 
	cat comandos.txt | ./stream-ui entrada.txt salida.txt

clean:
	rm *.o stream-ui stream-server stream-client