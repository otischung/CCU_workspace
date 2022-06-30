CXX=iverilog
SHOW=gtkwave

all: lab5

lab5: ./lab5_tb.v ./lab5.v
	$(CXX) $< -o $@

lab5.fsdb: lab5
	./$<

run: lab5.fsdb
	$(SHOW) $<

clean:
	rm -f lab5 lab5.fsdb
