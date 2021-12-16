CC?=gcc-11
CFLAGS=-g
CLIB=-lpcap

all: pcap_parse

pcap_parse: ./pcap_parse.c
	${CC} ${CFLAGS} pcap_parse.c -o pcap_parse ${CLIB}

clean: 
	rm -f pcap_parse
