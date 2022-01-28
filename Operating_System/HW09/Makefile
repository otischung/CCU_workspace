SHELL=/bin/bash
CC?=gcc-11
CFLAGS=-g -O3 -pthread -march=native
SRC=$(wildcard *.c)
EXE=$(patsubst %.c, %, $(SRC))
CLIB=-lm

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@ ${CLIB}

clean:
	rm ${EXE}

