SHELL=/bin/bash

all: tb16 tb32 tb64

tb16: ./16bit_testbench.v
	iverilog -o tb16bit 16bit_testbench.v
	vvp tb16bit | cat > log16bit.txt
	cat log16bit.txt
	gtkwave 16bit_CLS.fsdb &

tb32: ./16bit_testbench.v ./32bit_testbench.v
	iverilog -o tb32bit 32bit_testbench.v
	vvp tb32bit | cat > log32bit.txt
	cat log32bit.txt
	gtkwave 32bit_CLS.fsdb &

tb64: ./16bit_testbench.v ./64bit_testbench.v
	iverilog -o tb64bit 64bit_testbench.v
	vvp tb64bit | cat > log64bit.txt
	cat log64bit.txt
	gtkwave 64bit_CLS.fsdb &

clean:
	rm tb16bit tb32bit tb64bit log16bit.txt log32bit.txt log64bit.txt 16bit_CLS.fsdb 32bit_CLS.fsdb 64bit_CLS.fsdb
