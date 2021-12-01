CC?=gcc-11
CFLAGS=-g

all: OX_server OX_client

OX_server: ./OX_server_main.c ./serve_client.h ./states.h ./utils.h
	${CC} ${CFLAGS} OX_server_main.c -o OX_server

OX_client: ./OX_client_main.c ./client_impl.h ./states.h ./utils.h
	${CC} ${CFLAGS} OX_client_main.c -o OX_client

clean:
	rm OX_server OX_client
