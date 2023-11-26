CC = gcc
CFLAGS = -Wall
LIBS = -lncurses

all: exemplul1 exemplul2 exemplul3 exemplul4 clock

exemplul1: exemplul1.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

exemplul2: exemplul2.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

exemplul3: exemplul3.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

exemplul4: exemplul4.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clock: clock.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f exemplul1 exemplul2 exemplul3 exemplul4 clock
