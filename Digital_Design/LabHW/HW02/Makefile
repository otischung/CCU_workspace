CC=iverilog
SRC=$(wildcard *.v)
TARGET=add4

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $(TARGET)

clean:
	rm -f $(TARGET)
