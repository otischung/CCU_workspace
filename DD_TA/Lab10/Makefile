FLAGS=-g2012

all: lab10

lab10: lab10tb.v lab10ans.v
	iverilog $(FLAGS) $^ -o $@

Lab.vcd: lab10
	./$<

run: Lab.vcd
	gtkwave $< > /dev/null 2>&1 &

clean:
	rm -f lab10 Lab.vcd
