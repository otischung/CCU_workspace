// $ANTLR 3.4 Expr.g 2012-04-16 11:29:45

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked"})
public class ExprParser extends Parser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "Number", "WS", "'('", "')'", "'*'", "'+'", "'-'", "'/'"
    };

    public static final int EOF=-1;
    public static final int T__6=6;
    public static final int T__7=7;
    public static final int T__8=8;
    public static final int T__9=9;
    public static final int T__10=10;
    public static final int T__11=11;
    public static final int Number=4;
    public static final int WS=5;

    // delegates
    public Parser[] getDelegates() {
        return new Parser[] {};
    }

    // delegators


    public ExprParser(TokenStream input) {
        this(input, new RecognizerSharedState());
    }
    public ExprParser(TokenStream input, RecognizerSharedState state) {
        super(input, state);
    }

    public String[] getTokenNames() { return ExprParser.tokenNames; }
    public String getGrammarFileName() { return "Expr.g"; }



    // $ANTLR start "eval"
    // Expr.g:4:1: eval : additionExp ;
    public final void eval() throws RecognitionException {
        try {
            // Expr.g:5:5: ( additionExp )
            // Expr.g:5:10: additionExp
            {
            pushFollow(FOLLOW_additionExp_in_eval19);
            additionExp();

            state._fsp--;


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }

        finally {
        	// do for sure before leaving
        }
        return ;
    }
    // $ANTLR end "eval"



    // $ANTLR start "additionExp"
    // Expr.g:9:1: additionExp : multiplyExp ( '+' multiplyExp | '-' multiplyExp )* ;
    public final void additionExp() throws RecognitionException {
        try {
            // Expr.g:10:5: ( multiplyExp ( '+' multiplyExp | '-' multiplyExp )* )
            // Expr.g:10:10: multiplyExp ( '+' multiplyExp | '-' multiplyExp )*
            {
            pushFollow(FOLLOW_multiplyExp_in_additionExp45);
            multiplyExp();

            state._fsp--;


            // Expr.g:11:10: ( '+' multiplyExp | '-' multiplyExp )*
            loop1:
            do {
                int alt1=3;
                int LA1_0 = input.LA(1);

                if ( (LA1_0==9) ) {
                    alt1=1;
                }
                else if ( (LA1_0==10) ) {
                    alt1=2;
                }


                switch (alt1) {
            	case 1 :
            	    // Expr.g:11:12: '+' multiplyExp
            	    {
            	    match(input,9,FOLLOW_9_in_additionExp59); 

            	    pushFollow(FOLLOW_multiplyExp_in_additionExp61);
            	    multiplyExp();

            	    state._fsp--;


            	    }
            	    break;
            	case 2 :
            	    // Expr.g:12:12: '-' multiplyExp
            	    {
            	    match(input,10,FOLLOW_10_in_additionExp75); 

            	    pushFollow(FOLLOW_multiplyExp_in_additionExp77);
            	    multiplyExp();

            	    state._fsp--;


            	    }
            	    break;

            	default :
            	    break loop1;
                }
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }

        finally {
        	// do for sure before leaving
        }
        return ;
    }
    // $ANTLR end "additionExp"



    // $ANTLR start "multiplyExp"
    // Expr.g:17:1: multiplyExp : atomExp ( '*' atomExp | '/' atomExp )* ;
    public final void multiplyExp() throws RecognitionException {
        try {
            // Expr.g:18:5: ( atomExp ( '*' atomExp | '/' atomExp )* )
            // Expr.g:18:10: atomExp ( '*' atomExp | '/' atomExp )*
            {
            pushFollow(FOLLOW_atomExp_in_multiplyExp112);
            atomExp();

            state._fsp--;


            // Expr.g:19:10: ( '*' atomExp | '/' atomExp )*
            loop2:
            do {
                int alt2=3;
                int LA2_0 = input.LA(1);

                if ( (LA2_0==8) ) {
                    alt2=1;
                }
                else if ( (LA2_0==11) ) {
                    alt2=2;
                }


                switch (alt2) {
            	case 1 :
            	    // Expr.g:19:12: '*' atomExp
            	    {
            	    match(input,8,FOLLOW_8_in_multiplyExp125); 

            	    pushFollow(FOLLOW_atomExp_in_multiplyExp127);
            	    atomExp();

            	    state._fsp--;


            	    }
            	    break;
            	case 2 :
            	    // Expr.g:20:12: '/' atomExp
            	    {
            	    match(input,11,FOLLOW_11_in_multiplyExp141); 

            	    pushFollow(FOLLOW_atomExp_in_multiplyExp143);
            	    atomExp();

            	    state._fsp--;


            	    }
            	    break;

            	default :
            	    break loop2;
                }
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }

        finally {
        	// do for sure before leaving
        }
        return ;
    }
    // $ANTLR end "multiplyExp"



    // $ANTLR start "atomExp"
    // Expr.g:27:1: atomExp : ( Number | '(' additionExp ')' );
    public final void atomExp() throws RecognitionException {
        try {
            // Expr.g:28:5: ( Number | '(' additionExp ')' )
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0==Number) ) {
                alt3=1;
            }
            else if ( (LA3_0==6) ) {
                alt3=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 3, 0, input);

                throw nvae;

            }
            switch (alt3) {
                case 1 :
                    // Expr.g:28:10: Number
                    {
                    match(input,Number,FOLLOW_Number_in_atomExp178); 

                    }
                    break;
                case 2 :
                    // Expr.g:29:15: '(' additionExp ')'
                    {
                    match(input,6,FOLLOW_6_in_atomExp194); 

                    pushFollow(FOLLOW_additionExp_in_atomExp196);
                    additionExp();

                    state._fsp--;


                    match(input,7,FOLLOW_7_in_atomExp198); 

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }

        finally {
        	// do for sure before leaving
        }
        return ;
    }
    // $ANTLR end "atomExp"

    // Delegated rules


 

    public static final BitSet FOLLOW_additionExp_in_eval19 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_multiplyExp_in_additionExp45 = new BitSet(new long[]{0x0000000000000602L});
    public static final BitSet FOLLOW_9_in_additionExp59 = new BitSet(new long[]{0x0000000000000050L});
    public static final BitSet FOLLOW_multiplyExp_in_additionExp61 = new BitSet(new long[]{0x0000000000000602L});
    public static final BitSet FOLLOW_10_in_additionExp75 = new BitSet(new long[]{0x0000000000000050L});
    public static final BitSet FOLLOW_multiplyExp_in_additionExp77 = new BitSet(new long[]{0x0000000000000602L});
    public static final BitSet FOLLOW_atomExp_in_multiplyExp112 = new BitSet(new long[]{0x0000000000000902L});
    public static final BitSet FOLLOW_8_in_multiplyExp125 = new BitSet(new long[]{0x0000000000000050L});
    public static final BitSet FOLLOW_atomExp_in_multiplyExp127 = new BitSet(new long[]{0x0000000000000902L});
    public static final BitSet FOLLOW_11_in_multiplyExp141 = new BitSet(new long[]{0x0000000000000050L});
    public static final BitSet FOLLOW_atomExp_in_multiplyExp143 = new BitSet(new long[]{0x0000000000000902L});
    public static final BitSet FOLLOW_Number_in_atomExp178 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_6_in_atomExp194 = new BitSet(new long[]{0x0000000000000050L});
    public static final BitSet FOLLOW_additionExp_in_atomExp196 = new BitSet(new long[]{0x0000000000000080L});
    public static final BitSet FOLLOW_7_in_atomExp198 = new BitSet(new long[]{0x0000000000000002L});

}