all: mylexer.class

antlr-4.9.3-complete.jar:
	./Download_antlr-4.9.3-complete.jar.sh

mylexer.java mylexer.tokens: mylexer.g antlr-4.9.3-complete.jar
	java -jar ./antlr-4.9.3-complete.jar $<

mylexer.class: mylexer.java testLexer.java
	javac -cp ./antlr-4.9.3-complete.jar $^

%:
	@:

args=$(filter-out $@,$(MAKECMDGOALS))

run: mylexer.class
	java -cp ./antlr-4.9.3-complete.jar:. testLexer $(args)

clean: 
	rm -f mylexer.java mylexer.tokens mylexer.interp
