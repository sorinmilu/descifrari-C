CC = gcc
CFLAGS = -Wall -g

SRC = main.c board.c
OBJ = $(SRC:.c=.o)
TARGET = ttt

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
