SHELL = /bin/bash
CC = gcc
CFLAGS = -g
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@

clean:
	rm ./bin/*
