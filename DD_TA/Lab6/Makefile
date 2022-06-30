CXX=iverilog
SHOW=gtkwave

all: mul lab6_demo

mul: testbench.v multiplier.v
	$(CXX) $< -o $@

mul.fsdb: mul
	./$<

run: mul.fsdb
	$(SHOW) $< > /dev/null 2>&1 &

lab6_demo: lab6_demo.cpp
	g++ -O3 $< -o $@

clean:
	rm -f mul.fsdb mul lab6_demo
