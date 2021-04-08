SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	# mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o $@
	ln -s $@ cp
	ln -s $@ ls
	ln -s $@ cat
	ln -s $@ chown

clean:
	# rm -f ./bin/*
	rm cp ls cat chown ${EXE}