CC?=gcc-11
CFLAGS=-g -mavx
SRC=$(wildcard *.c)
TARGET=$(patsubst %.c, %, ${SRC})

all: ${TARGET}
%:	%.c
	${CC} ${CFLAGS} $< -o $@

clean: 
	rm -f ${TARGET} data.txt output.txt output_simd.txt
