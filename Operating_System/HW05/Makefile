SHELL=/bin/bash
CC=gcc
CFLAGS=-g -pthread -O3 -fsanitize=address -fsanitize=leak -fsanitize=undefined
CLIB=-lm
SRC=$(wildcard *.c)
EXE=$(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@ ${CLIB}

clean:
	rm -f ./bin/*
