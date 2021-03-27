SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread -z lazy -pg -finstrument-functions
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	cp -f input.txt output.txt ./bin/
	${CC} ${CFLAGS} $@.c -o ./bin/$@

clean:
	rm ./bin/*
