# Makefile

CC = gcc
CFLAGS = -Wall

all: simple_list

simple_list: main.o list_functions.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c list_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

list_functions.o: list_functions.c list_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o simple_list
