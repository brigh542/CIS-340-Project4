CC = gcc

CFLAGS = -std=gnu99 -Wall -g -c

EXECS = server client



all: $(EXECS)



server: server.o

	$(CC) server.o -o server



server.o: server.c

	$(CC) $(CFLAGS) server.c



client: client.o 

	$(CC) client.o -o client



client.o: client.c

	$(CC) $(CFLAGS) client.c



clean:

	$(RM) *.o $(EXECS)
