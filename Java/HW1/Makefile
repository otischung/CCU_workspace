CXX=javac
CFLAGS=-g
SRC=$(wildcard *.java)
TARGET=$(patsubst %.java, %.class, $(SRC))

all: $(TARGET)

%.class: %.java
	$(CXX) $(CFLAGS) $<

clean:
	rm -f $(TARGET) 'TicTacToe$$1.class' 'TicTacToe$$Game.class' 'TicTacToe$$State.class'
