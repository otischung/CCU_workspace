CXX=g++
CFLAGS=-g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=leak

all: main

main: main.cpp Time.cpp Time.h
	$(CXX) $(CFLAGS) main.cpp Time.cpp -o $@

clean:
	rm -f main
