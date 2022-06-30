import org.antlr.v4.runtime.*;

public class myCompiler_test {
    /**
     * @param args
     */
    public static void main(String[] args) {

        // TODO Auto-generated method stub
        try {
            CharStream input = new ANTLRFileStream(args[0]);
            myCompilerLexer lexer = new myCompilerLexer(input);
            // ---------- For debug ----------
            // myparserLexer lexer_print = new myparserLexer(input);
            // Token token = lexer_print.nextToken();
            // while (token.getType() != -1) { // -1 is EOF.
            //     System.out.println("Token: " + token.getType() + " " + token.getText());
            //     token = lexer_print.nextToken();
            // }
            // ---------- For debug ----------
            CommonTokenStream tokens = new CommonTokenStream(lexer);

            myCompilerParser parser = new myCompilerParser(tokens);
            parser.translationUnit();
        } catch (Throwable t) {
            System.out.println("Exception: " + t);
            t.printStackTrace();
        }
    }

}
