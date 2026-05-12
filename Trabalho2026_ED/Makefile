CC = gcc
CFLAGS = -Wall -Wextra -I include

SRC = main.c src/*.c
OUT = programa

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)