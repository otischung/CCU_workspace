SHELL = /bin/bash
CC = gcc
CFLAGS = -g -z lazy -pthread

all: ./nice_testing.c
	mkdir -p ./bin
	${CC} ${CFLAGS} nice_testing.c -o ./bin/nice_testing
	sudo setcap CAP_CHOWN+ep ./bin/nice_testing

test: stest stest2 ltest ltest2

stest: all
	time strace -c ./bin/nice_testing 5
	time strace -c taskset 0x1 ./bin/nice_testing 5

stest2: all
	time strace -c ./bin/nice_testing -5
	time strace -c taskset 0x1 ./bin/nice_testing -5

ltest: all
	time ltrace -c ./bin/nice_testing 5
	time ltrace -c taskset 0x1 ./bin/nice_testing 5

ltest2: all
	time ltrace -c ./bin/nice_testing -5
	time ltrace -c taskset 0x1 ./bin/nice_testing -5

clean:
	rm -f ./bin/*
