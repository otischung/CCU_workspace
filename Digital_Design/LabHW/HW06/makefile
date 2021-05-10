SHELL=/bin/bash

all: tb1 tb2 tb2.1

tb1: ./16bit_testbench.v
	iverilog -o tb1 16bit_testbench.v
	vvp tb1 | cat > logtb1.txt
	cat logtb1.txt
	gtkwave 16bit_RCA.fsdb &

tb2: ./16bit_testbench2.v
	iverilog -o tb2 16bit_testbench2.v
	vvp tb2
	gtkwave 16bit_RCA2.fsdb &

tb2.1: ./16bit_testbench2.1.v
	iverilog -o tb2.1 16bit_testbench2.1.v
	vvp tb2.1
	gtkwave 16bit_RCA2.1.fsdb &

clean:
	rm tb1 tb2 tb2.1 logtb1.txt 16bit_RCA.fsdb 16bit_RCA2.fsdb 16bit_RCA2.1.fsdb
