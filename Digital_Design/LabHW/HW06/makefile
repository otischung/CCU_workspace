SHELL=/bin/bash

all: tb1 tb2

tb1: ./16bit_testbench.v
	iverilog -o tb1 16bit_testbench.v
	vvp tb1 | cat > logtb1.txt
	cat logtb1.txt
	gtkwave 16bit_RCA.fsdb &

tb2: ./16bit_testbench2.v
	iverilog -o tb2 16bit_testbench2.v
	vvp tb2 | cat > logtb2.txt
	cat logtb2.txt
	gtkwave 16bit_RCA2.fsdb &

clean:
	rm tb1 tb2 logtb1.txt logtb2.txt 16bit_RCA.fsdb 16bit_RCA2.fsdb
