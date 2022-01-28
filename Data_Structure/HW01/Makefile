CC?=gcc-11
CFLAGS=-g
CLIB=-lm

all: erasure_code

erasure_code: ./erasure_code.c
	${CC} ${CFLAGS} erasure_code.c -o erasure_code ${CLIB}

clean: 
	rm erasure_code
