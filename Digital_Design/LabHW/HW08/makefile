all: ./sign_ext_mpy_8bit.v ./testbench.v
	iverilog -o test testbench.v
	vvp test | cat > log.txt
	cat log.txt
	gtkwave MPY.fsdb &

clean:
	rm -f test log.txt MPY.fsdb
