all: myInterp_test.class

antlr-4.9.3-complete.jar:
	./Download_antlr-4.9.3-complete.jar.sh

myInterpLexer.java myInterpParser.java myInterp.tokens: myInterp.g antlr-4.9.3-complete.jar
	java -jar ./antlr-4.9.3-complete.jar $<

myInterp_test.class: myInterpLexer.java myInterpParser.java myInterpBaseListener.java myInterpListener.java myInterp_test.java RValTemp.java Label.java
	javac -cp ./antlr-4.9.3-complete.jar $^

%:
	@:

args=$(filter-out $@,$(MAKECMDGOALS))

run: myInterp_test.class
	java -cp ./antlr-4.9.3-complete.jar:. myInterp_test $(args)

draw: myInterp_test.class
	java -cp ./antlr-4.9.3-complete.jar:. org.antlr.v4.gui.TestRig myInterp translationUnit -gui $(args)

clean: 
	rm -f myInterp.tokens myInterp.interp myInterpBaseListener.java myInterpLexer.java myInterpLexer.interp myInterpLexer.tokens myInterpListener.java myInterpParser.java $(wildcard *.class) $(patsubst %, '%', $(wildcard myInterpParser$$*.class))
