CC=g++
CFLAGS=-g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=leak

all: hw4 main

hw4: hw4.cpp Grid.cpp Grid.h
	$(CC) $(CFLAGS) hw4.cpp Grid.cpp -o $@

main: main.cpp Grid.cpp Grid.h
	$(CC) $(CFLAGS) main.cpp Grid.cpp -o $@

clean:
	rm -f hw4 main
