CC=g++
CFLAGS=-g -Wall -fsanitize=leak -fsanitize=address -fsanitize=undefined
SRC=$(wildcard *.cpp)
TARGET=$(patsubst %.cpp, %, $(SRC))

all: $(TARGET) $(JTARGET)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
