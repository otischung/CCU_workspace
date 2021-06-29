all: mealy moore

mealy: ./mealy_hw.v ./tb_mealy.v
	iverilog -o mealy tb_mealy.v
	vvp mealy
	gtkwave hw_mealy.fsdb

moore: ./moore_hw.v ./tb_moore.v
	iverilog -o moore tb_moore.v
	vvp moore
	gtkwave hw_moore.fsdb

clean:
	rm -f mealy moore hw_mealy.fsdb hw_moore.fsdb
