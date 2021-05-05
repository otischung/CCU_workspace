SHELL=/bin/bash
CC=gcc
CFLAGS=-g -z lazy
SRC=$(wildcard *.c)
TARGET=$(patsubst %.c, %, $(SRC))

all: ${TARGET}
%:	%.c
	${CC} ${CFLAGS} $@.c -o $@ -lpthread

clean:
	rm ${TARGET} *.txt

