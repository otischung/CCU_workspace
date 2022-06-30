import org.antlr.runtime.*;

public class myC_new_test {
	public static void main(String[] args) throws Exception {

      CharStream input = new ANTLRFileStream(args[0]);
      myC_newLexer lexer = new myC_newLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
 
      myC_newParser parser = new myC_newParser(tokens);
      parser.program();
	}
}
