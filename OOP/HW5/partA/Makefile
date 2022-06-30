CXX=g++
CFLAGS=-g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=leak

all: main

main: main.cpp Cube.cpp Cube.h
	$(CXX) $(CFLAGS) main.cpp Cube.cpp -o $@

clean:
	rm -f main
