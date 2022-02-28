CC=iverilog

all: lab5

lab5: ./tb_lab5.v ./lab5.v
	$(CC) $< -o $@

run: lab5
	rm -f log.txt
	./lab5 | cat > log.txt
	cat log.txt
	gtkwave lab5.fsdb &

clean:
	rm -f lab5 lab5.fsdb log.txt
