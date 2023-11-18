CC = gcc
CFLAGS = -Wall -Wextra

all: socket_server socket_client

server: server.c
	$(CC) $(CFLAGS) -o socket_server server.c

client: client.c
	$(CC) $(CFLAGS) -o socket_client socket_client.c

.PHONY: clean

clean:
	rm -f socket_server socket_client