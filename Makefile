CC=gcc
CFLAGS=-std=c11 -O2 -Wall
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
BIN=eval3_c

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BIN) src/*.o

.PHONY: all clean
