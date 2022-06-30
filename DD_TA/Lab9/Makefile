all: lab9

lab9: lab9_tb.v lab9ans.v
	iverilog $^ -o $@

Lab.vcd: lab9
	./$<

run: Lab.vcd
	gtkwave $< > /dev/null 2>&1 &

clean:
	rm -f lab9 Lab.vcd
