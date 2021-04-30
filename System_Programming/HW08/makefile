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
	@echo -e '\n'
	time strace -c taskset 0x1 ./bin/nice_testing 5
	@echo -e '\n'

stest2: all
	time strace -c ./bin/nice_testing -5
	@echo -e '\n'
	time strace -c taskset 0x1 ./bin/nice_testing -5
	@echo -e '\n'

ltest: all
	time ltrace -c ./bin/nice_testing 5
	@echo -e '\n'
	time ltrace -c taskset 0x1 ./bin/nice_testing 5
	@echo -e '\n'

ltest2: all
	time ltrace -c ./bin/nice_testing -5
	@echo -e '\n'
	time ltrace -c taskset 0x1 ./bin/nice_testing -5
	@echo -e '\n'

clean:
	rm -f ./bin/*
