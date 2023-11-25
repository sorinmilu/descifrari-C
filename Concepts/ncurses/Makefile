CC = gcc
CFLAGS = -Wall
LIBS = -lncurses

all: hei exemplul1 exemplul2 clock

hei: hei.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

exemplul1: exemplul1.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

exemplul2: exemplul2.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clock: clock.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f hei exemplul1 exemplul2 clock
