SHELL = /bin/bash
CC = gcc
CFLAGS = -g -z -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@
	sudo chmod +s ./bin/$@

clean:
	rm -f ./bin/*
