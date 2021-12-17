CC?=gcc-11
CFLAGS=-g
CLIB=-lpcap

all: pcap_parse

ipv4.o: ./ipv4.c ./ipv4.h
	${CC} ${CFLAGS} -c ipv4.c

pcap_parse.o: ./pcap_parse.c
	${CC} ${CFLAGS} -c pcap_parse.c

pcap_parse: ipv4.o pcap_parse.o
	${CC} pcap_parse.o ipv4.o -o pcap_parse ${CLIB}

clean: 
	rm -f pcap_parse ipv4.o pcap_parse.o
