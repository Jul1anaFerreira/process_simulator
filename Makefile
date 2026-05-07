CC=gcc
CFLAGS=-Wall -Wextra -Iinclude

SRC=src/main.c src/process.c src/scheduler.c src/memory.c
OUT=simulator

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)