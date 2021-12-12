CC?=gcc-11
CFLAGS=-g
CLIB=-lpcap

all: tcpdump

tcpdump: ./tcpdump.c
	${CC} ${CFLAGS} tcpdump.c -o tcpdump ${CLIB}

clean: 
	rm -f tcpdump
