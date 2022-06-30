CXX=iverilog
SHOWER=gtkwave

all: Lab4

Lab4: testbench.v Lab4.v sample.v
	$(CXX) $< -o $@

Lab4.fsdb: Lab4
	./$<

run: Lab4.fsdb
	$(SHOWER) $< > /dev/null 2>&1 & 

clean:
	rm -f Lab4 Lab4.fsdb
