CC?=gcc-11
CFLAGS=-g -fsanitize=address -fsanitize=leak -fsanitize=undefined

all: data_sink

data_sink: ./data_sink.c
	${CC} ${CFLAGS} data_sink.c -o data_sink

expand: ./data_sink.c
	rm -f data_sink_expand.c
	${CC} -E data_sink.c > data_sink_expand.c

data_sink_by_Ray: ./data_sink_by_Ray.c
	${CC} ${CFLAGS} data_sink_by_Ray.c -o data_sink_by_Ray

clean:
	rm -f data_sink
