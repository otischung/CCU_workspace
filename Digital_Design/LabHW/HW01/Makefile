CC=iverilog
SRC=$(wildcard *.v)
TARGET=test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $(TARGET)

clean:
	rm -f $(TARGET)
