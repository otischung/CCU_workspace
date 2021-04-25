SHELL=/bin/bash
CC=gcc
CFLAGS=-g -z lazy -pthread
SRC=$(wildcard *.c)
TARGET=$(patsubst %.c, %, $(SRC))

all: ${TARGET}
	${CC} ${CFLAGS} random_string_generater.c -o random_string_generater
	${CC} ${CFLAGS} random_int_generater.c -o random_int_generater
	${CC} ${CFLAGS} sortperf_string.c -o sortperf_string
	ln -s sortperf_string mergesort_string
	ln -s sortperf_string heapsort_string
	ln -s sortperf_string quicksort_string
	${CC} ${CFLAGS} sortperf.c -o sortperf
	ln -s sortperf mergesort
	ln -s sortperf heapsort
	ln -s sortperf quicksort

gen: ./random_string_generater ./random_int_generater
	time strace -c ./random_string_generater
	time strace -c ./random_int_generater

clean:
	rm ${TARGET} mergesort heapsort quicksort mergesort_string heapsort_string quicksort_string

clean_gen:
	rm random_int.txt random_string.txt