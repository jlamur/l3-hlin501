CC=g++
CFLAGS=-W -Wall -ansi -pedantic

.PHONY=clean tp1 tp2

all: tp1 tp2

tp1: src/tp1.cpp
	$(CC) src/tp1.cpp -o tp1 $(CFLAGS)

tp2: src/tp2.cpp
	$(CC) src/tp2.cpp -o tp2 $(CFLAGS)

clean:
	rm -f tp1 tp2
