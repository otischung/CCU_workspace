SHELL = /bin/bash
CC := iverilog
CFLAGS := -o
SRC := *.v
EXE := add4

all:
	mkdir -p bin	
	${CC} ${CFLAGS} ./bin/${EXE} ${SRC}

run: all
	vvp ./bin/${EXE} | cat > log.txt
	cat log.txt
	mv ${EXE}.vcd ./bin
	gtkwave ./bin/${EXE}.vcd & disown

clean:
	rm ./bin/*
