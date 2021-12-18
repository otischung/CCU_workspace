CC?=gcc-11
CFLAGS=-g
CLIB=-lpcap

all: pcap_parse

network.o: ./network.c ./network.h ./headers.h
	${CC} ${CFLAGS} -c network.c

transport.o: ./transport.c ./transport.h ./headers.h
	${CC} ${CFLAGS} -c transport.c

pcap_parse.o: ./pcap_parse.c ./headers.h
	${CC} ${CFLAGS} -c pcap_parse.c

pcap_parse: network.o transport.o pcap_parse.o
	${CC} pcap_parse.o network.o transport.o -o pcap_parse ${CLIB}

clean: 
	rm -f pcap_parse network.o pcap_parse.o transport.o
