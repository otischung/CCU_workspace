SHELL = /bin/bash
CC = gcc
CFLAGS = -g -O3 -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@

clean:
	rm -f ./bin/*
