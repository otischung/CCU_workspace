all: testParser.class

antlr-4.9.3-complete.jar:
	./Download_antlr-4.9.3-complete.jar.sh

myparserLexer.java myparserParser.java myparser.tokens: myparser.g antlr-4.9.3-complete.jar
	java -jar ./antlr-4.9.3-complete.jar $<

testParser.class: myparserLexer.java myparserParser.java myparserBaseListener.java myparserListener.java testParser.java
	javac -cp ./antlr-4.9.3-complete.jar $^

%:
	@:

args=$(filter-out $@,$(MAKECMDGOALS))

run: testParser.class
	java -cp ./antlr-4.9.3-complete.jar:. testParser $(args)

draw: testParser.class
	java -cp ./antlr-4.9.3-complete.jar:. org.antlr.v4.gui.TestRig myparser translationUnit -gui $(args)

clean: 
	rm -f myparser.tokens myparser.interp myparserBaseListener.java myparserLexer.java myparserLexer.interp myparserLexer.tokens myparserListener.java myparserParser.java $(wildcard *.class) $(patsubst %, '%', $(wildcard myparserParser$$*.class))
