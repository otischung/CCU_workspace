CXX=g++
CFLAGS=-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
TARGET=$(patsubst %.cpp, %, $(wildcard *.cpp))

all: $(TARGET)

%: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
