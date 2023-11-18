CC = gcc
CFLAGS = -Wall -Wextra

all: daemon_example

daemon_example: daemon_example.c
	$(CC) $(CFLAGS) -o daemon_example daemon_example.c

.PHONY: clean

clean:
	rm -f daemon_example