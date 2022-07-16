CC=gcc

SRC=$(wildcard src/*.c)

all: everything

everything: $(SRC)
	$(CC) -o wordle $(SRC)

clean:
	rm wordle