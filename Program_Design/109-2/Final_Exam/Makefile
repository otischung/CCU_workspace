SHELL=/bin/bash
CC?=gcc-10
CFLAGS=-g -pthread -fsanitize=undefined -fsanitize=address
CLIB=-lm -lacl
SRC=$(wildcard *.c)
TARGET=$(patsubst %.c, %, $(SRC))

all: ${TARGET}
%: %.c
	${CC} ${CFLAGS} $@.c -o $@ ${CLIB}

clean:
	rm -f ${TARGET}
