SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@
	ln -s ${PWD}/bin/$@ ./bin/cp
	ln -s ${PWD}/bin/$@ ./bin/ls
	ln -s ${PWD}/bin/$@ ./bin/cat
	ln -s ${PWD}/bin/$@ ./bin/chown

clean:
	rm -f ./bin/*
	