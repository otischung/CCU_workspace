SHELL=/bin/bash
CC=gcc
CFLAGS=-g -z lazy -pthread

all:
	${CC} ${CFLAGS} sortperf.c -o sortperf
	ln -s sortperf mergesort
	ln -s sortperf heapsort
	ln -s sortperf quicksort

clean:
	rm sortperf mergesort heapsort quicksort
