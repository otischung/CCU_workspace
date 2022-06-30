CC=g++
JC=javac
CFLAGS=-g -Wall -fsanitize=leak -fsanitize=address -fsanitize=undefined
JFLAGS=-g -Xlint:all
CSRC=$(wildcard *.cpp)
JSRC=$(wildcard *.java)
CTARGET=$(patsubst %.cpp, %, $(CSRC))
JTARGET=$(patsubst %.java, %.class, $(JSRC))

all: $(CTARGET) $(JTARGET)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

%.class: %.java
	$(JC) $(JFLAGS) $<

clean:
	rm -f $(CTARGET) $(JTARGET)
