SHELL = /bin/bash
CC = gcc
CFLAGS = -g --static
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@
	sudo chown root $@
	sudo chmod +s $@
	ln -s $@ ./lazyshell
	ln -s $@ ./ln
	ln -s $@ ./stat
	ln -s $@ ./chown

clean:
	rm -f ${EXE} lazyshell ln stat chown .sudo_success
