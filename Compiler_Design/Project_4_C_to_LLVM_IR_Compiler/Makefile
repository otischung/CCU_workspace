all: myCompiler_test.class

antlr-4.9.3-complete.jar:
	./Download_antlr-4.9.3-complete.jar.sh

myCompilerLexer.java myCompilerParser.java myCompiler.tokens: myCompiler.g antlr-4.9.3-complete.jar
	java -jar ./antlr-4.9.3-complete.jar $<

myCompiler_test.class: myCompilerLexer.java myCompilerParser.java myCompilerBaseListener.java myCompilerListener.java myCompiler_test.java
	javac -cp ./antlr-4.9.3-complete.jar $^

%:
	@:

args=$(filter-out $@,$(MAKECMDGOALS))

run: myCompiler_test.class
	java -cp ./antlr-4.9.3-complete.jar:. myCompiler_test $(args)

draw: myCompiler_test.class
	java -cp ./antlr-4.9.3-complete.jar:. org.antlr.v4.gui.TestRig myCompiler translationUnit -gui $(args)

clean:
	rm -f myCompiler.tokens myCompiler.interp myCompilerBaseListener.java myCompilerLexer.java myCompilerLexer.interp myCompilerLexer.tokens myCompilerListener.java myCompilerParser.java $(wildcard *.class) $(patsubst %, '%', $(wildcard myCompilerParser$$*.class)) $(patsubst %, '%', $(wildcard myCompilerLexer$$*.class))
