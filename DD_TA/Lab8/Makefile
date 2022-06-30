all: lab8

lab8: lab8ans.v lab8_tb.v
	iverilog $^ -o $@

Lab.vcd: lab8
	./$<

run: Lab.vcd
	gtkwave $< > /dev/null 2>&1 &

clean:
	rm -f lab8 Lab.vcd
