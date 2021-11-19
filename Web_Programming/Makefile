CC?=gcc-11
CFLAGS=-g
SRC=$(wildcard *.c)
TARGET=$(patsubst %.c, %, $(SRC))

all: ${TARGET}
%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${TARGET}
