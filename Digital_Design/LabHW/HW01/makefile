SHELL = /bin/bash
CC := iverilog
CFLAGS := -o
SRC := *.v
EXE := test4

all:
	mkdir -p bin	
	${CC} ${CFLAGS} ./bin/${EXE} ${SRC}

run: all
	vvp ./bin/${EXE}

log: all
	vvp ./bin/${EXE} | cat > log.txt

clean:
	rm ./bin/*
