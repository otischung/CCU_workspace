SHELL=/bin/bash

all: ./16bit_testbench.v
	iverilog -o tb1 16bit_testbench.v
	vvp tb1 | cat > log.txt
	cat log.txt
	gtkwave 16bit_CLA.fsdb &

clean:
	rm tb1 log.txt 16bit_CLA.fsdb
