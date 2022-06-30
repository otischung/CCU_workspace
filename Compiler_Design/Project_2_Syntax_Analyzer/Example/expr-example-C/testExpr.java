import org.antlr.runtime.*;

public class testExpr {
    public static void main(String[] args) throws Exception
    {
        CharStream input = new ANTLRFileStream(args[0]);
        ExprLexer lexer = new ExprLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
	
        ExprParser parser = new ExprParser(tokens);
        parser.eval();
    }
}

