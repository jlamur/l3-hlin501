CC=g++
CFLAGS=-W -Wall -ansi -pedantic

.PHONY=clean

all: tp1

tp1: src/tp1.cpp
	$(CC) src/tp1.cpp -o tp1 $(CFLAGS)

clean:
	rm -rf build
