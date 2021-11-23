CC?=gcc-11
CFLAGS=-g
SRC=$(wildcard *.c)
TAR=$(patsubst %.c, %, $(SRC))
CLIB=-lacl -lcurl

all: ${TAR}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${TAR}
