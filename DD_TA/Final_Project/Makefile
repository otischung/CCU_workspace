FLAGS=-g2012

all: JAM

JAM: tb.v JAMans.v
	iverilog $(FLAGS) $^ -o $@

JAM.vcd: JAM
	./$<

run: JAM.vcd
	gtkwave $< > /dev/null 2>&1 &

clean:
	rm -f JAM JAM.vcd
