SHELL=/bin/bash
CC=gcc
CFLAGS=-g -z lazy -pthread
CLIBS=-lcrypt

all: ./mylogin.c
	mkdir -p ./bin
	${CC} ${CFLAGS} mylogin.c -o ./bin/mylogin ${CLIBS}
	sudo chown root:root ./bin/mylogin
	sudo chmod +s ./bin/mylogin

clean:
	rm -f ./bin/*
