SHELL = /bin/bash
CC = gcc
CFLAGS ?= -g -z lazy # -fsanitize=undefined -fsanitize=address
LD_FLAGS ?= -pthread -lgc  --static
TARGETS=ln stat chown lazyshell lazysh
OUTPUT_DIR=bin
OBJ_DIR=/tmp
MAIN=${OUTPUT_DIR}/lazybox
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,${OBJ_DIR}/%.o,${SRC})
OUTPUTS = $(patsubst %,${OUTPUT_DIR}/%,${TARGETS})

all: ${MAIN} ${OUTPUTS}

${OUTPUTS}: %: ${MAIN} main.c
	ln -sf ${PWD}/${MAIN} ${PWD}/$@

${MAIN}: ${OBJ}
	mkdir -p ${OUTPUT_DIR}
	${CC} ${OBJ} ${CFLAGS} ${LD_FLAGS} -g  -o ${MAIN}
	sudo chown root ${MAIN}
	sudo chmod u+s ${MAIN}

${OBJ_DIR}/%.o: %.c
	mkdir -p ${OBJ_DIR}
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	rm -f ${OBJ}
	rm -f ${TARGETS}

