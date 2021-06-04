SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p bin
	cp -f test.txt ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@

clean:
	rm ./bin/*
