CC?=gcc-11
CFLAGS=-g
CLIB=-lacl -lcurl

all: web_server

web_server: ./web_server.c
	${CC} ${CFLAGS} web_server.c -o web_server

clean:
	rm web_server
