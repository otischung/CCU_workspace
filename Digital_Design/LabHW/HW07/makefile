CC=iverilog

all: tb4 tb16 tb64

tb4: ./4bit_testbench.v
	${CC} -o test4 4bit_testbench.v
	vvp test4 | cat > log4.txt
	cat log4.txt
	gtkwave CLA_4bit.fsdb &

tb16: ./16bit_testbench.v
	${CC} -o test16 16bit_testbench.v
	vvp test16 | cat > log16.txt
	cat log16.txt
	gtkwave CLA_16bit.fsdb &

tb64: ./64bit_testbench.v
	${CC} -o test64 64bit_testbench.v
	vvp test64 | cat > log64.txt
	cat log64.txt
	gtkwave CLA_64bit.fsdb &

clean:
	rm -f test4 test16 test64 log4.txt log16.txt log64.txt CLA_4bit.fsdb CLA_16bit.fsdb CLA_64bit.fsdb
