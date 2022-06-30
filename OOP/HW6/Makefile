CXX=g++
CFLAGS=-g -Wall -fsanitize=leak -fsanitize=address -fsanitize=undefined

all: main

main: main.cpp GameHandle.cpp GameHandle.h
	$(CXX) $(CFLAGS) main.cpp GameHandle.cpp -o $@

clean:
	rm -f main
