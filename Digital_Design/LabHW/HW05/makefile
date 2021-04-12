all: lab5.v tb_lab5.v
	iverilog -o test tb_lab5.v
	vvp test | cat > log.txt
	cat log.txt

run: all
	gtkwave lab5.fsdb &

clean:
	rm test lab5.fsdb