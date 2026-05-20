CC = gcc
CFLAGS = -Wall -Wextra -I include

SRC = main.c src/*.c
OUT = programa

.PHONY: all compile run clean

all: clean compile run

compile:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)