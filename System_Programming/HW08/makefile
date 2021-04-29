SHELL = /bin/bash
CC = gcc
CFLAGS = -g -z lazy -pthread

all: ./nice_testing.c
	mkdir -p ./bin
	${CC} ${CFLAGS} nice_testing.c -o ./bin/nice_testing
	sudo setcap CAP_CHOWN+ep ./bin/nice_testing

test: all
	./bin/nice_testing 5
	taskset 0x1 ./bin/nice_testing 5

clean:
	rm -f ./bin/*
