CC?=gcc-11
CFLAGS=-g

all: callandcall qsort

callandcall: ./callandcall.c
	${CC} ${CFLAGS} callandcall.c -o callandcall

qsort: ./qsort.c
	${CC} ${CFLAGS} qsort.c -o qsort

clean:
	rm callandcall qsort
