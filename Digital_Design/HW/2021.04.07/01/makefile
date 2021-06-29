SHELL=/bin/bash
CC=iverilog
SRC=$(wildcard *.v)

all: ${SRC}
	${CC} -o test ${SRC}
	vvp test | cat > ans.txt
	cat ans.txt

run: all
	gtkwave test.vcd &

clean:
	rm test test.vcd ans.txt
