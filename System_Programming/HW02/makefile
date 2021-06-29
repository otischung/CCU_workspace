SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

run: all
	./hole
	@printf '\n'
	time ./mycp2 FileHole FileHole2
	@printf '\n'
	time ./mmap_cp2 FileHole FileHole3
	@printf '\n'
	time ./mmap_cp FileHole FileHole4
	@printf '\n'
	ls -lash FileHole FileHole2 FileHole3 FileHole4
	@printf '\n'

clean:
	rm ${EXE}

clean_all:
	rm ${EXE} FileHole FileHole2 FileHole3 FileHole4
