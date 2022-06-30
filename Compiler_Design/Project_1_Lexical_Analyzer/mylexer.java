// Generated from mylexer.g by ANTLR 4.9.3
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class mylexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.3", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ASM_=1, BREAK_=2, CASE_=3, CHAR_TYPE=4, CONST_TYPE=5, CONTINUE_=6, DEFAULT_=7, 
		DO_=8, DOUBLE_TYPE=9, ELSE_=10, ENUM_=11, EXTERN_TYPE=12, FLOAT_TYPE=13, 
		FOR_=14, GOTO_=15, IF_=16, INT_TYPE=17, LONG_TYPE=18, PRAGMA_=19, REGISTER_=20, 
		RETURN_=21, SHORT_TYPE=22, SIGNED_TYPE=23, SIZEOF_=24, STATIC_=25, STRUCT_=26, 
		SWITCH_=27, TYPEDEF_=28, UNION_=29, UNSIGNED_TYPE=30, VOID_TYPE=31, VOLATILE_TYPE=32, 
		WHILE_=33, INCLUDE_=34, INCLUDE_LIB=35, INCLUDE_OWN=36, DEFINE_=37, STRING=38, 
		CHAR=39, ID=40, DEC_NUM=41, FLOAT_NUM=42, EQ_OP=43, LE_OP=44, GE_OP=45, 
		NE_OP=46, PP_OP=47, MM_OP=48, RSHIFT_OP=49, LSHIFT_OP=50, ASSIGN_OP=51, 
		AND_OP=52, COLON=53, COMMA=54, DIV_OP=55, GT_OP=56, LT_OP=57, MINUS_OP=58, 
		MODULO_OP=59, MULTI_OP_OR_POINTER=60, NOT_LOGIC_OP=61, NOT_BITWISE_OP=62, 
		OR_OP=63, PLUS_OP=64, SEMICOLON=65, XOR_OP=66, DOT=67, LEFT_PAREM=68, 
		RIGHT_PAREM=69, LEFT_BRACKET=70, RIGHT_BRACKET=71, LEFT_BRACE=72, RIGHT_BRACE=73, 
		COMMENT1=74, COMMENT2=75, WS=76, NEW_LINE=77;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"ASM_", "BREAK_", "CASE_", "CHAR_TYPE", "CONST_TYPE", "CONTINUE_", "DEFAULT_", 
			"DO_", "DOUBLE_TYPE", "ELSE_", "ENUM_", "EXTERN_TYPE", "FLOAT_TYPE", 
			"FOR_", "GOTO_", "IF_", "INT_TYPE", "LONG_TYPE", "PRAGMA_", "REGISTER_", 
			"RETURN_", "SHORT_TYPE", "SIGNED_TYPE", "SIZEOF_", "STATIC_", "STRUCT_", 
			"SWITCH_", "TYPEDEF_", "UNION_", "UNSIGNED_TYPE", "VOID_TYPE", "VOLATILE_TYPE", 
			"WHILE_", "INCLUDE_", "INCLUDE_LIB", "INCLUDE_OWN", "DEFINE_", "STRING", 
			"CHAR", "ID", "DEC_NUM", "FLOAT_NUM", "EQ_OP", "LE_OP", "GE_OP", "NE_OP", 
			"PP_OP", "MM_OP", "RSHIFT_OP", "LSHIFT_OP", "ASSIGN_OP", "AND_OP", "COLON", 
			"COMMA", "DIV_OP", "GT_OP", "LT_OP", "MINUS_OP", "MODULO_OP", "MULTI_OP_OR_POINTER", 
			"NOT_LOGIC_OP", "NOT_BITWISE_OP", "OR_OP", "PLUS_OP", "SEMICOLON", "XOR_OP", 
			"DOT", "LEFT_PAREM", "RIGHT_PAREM", "LEFT_BRACKET", "RIGHT_BRACKET", 
			"LEFT_BRACE", "RIGHT_BRACE", "COMMENT1", "COMMENT2", "WS", "NEW_LINE"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'asm'", "'break'", "'case'", "'char'", "'const'", "'continue'", 
			"'default'", "'do'", "'double'", "'else'", "'enum'", "'extern'", "'float'", 
			"'for'", "'goto'", "'if'", "'int'", "'long'", "'#pragma'", "'register'", 
			"'return'", "'short'", "'signed'", "'sizeof'", "'static'", "'struct'", 
			"'switch'", "'typedef'", "'union'", "'unsigned'", "'void'", "'volatile'", 
			"'while'", "'#include'", null, null, "'#define'", null, null, null, null, 
			null, "'=='", "'<='", "'>='", "'!='", "'++'", "'--'", "'<<'", "'>>'", 
			"'='", "'&'", "':'", "','", "'/'", "'>'", "'<'", "'-'", "'%'", null, 
			"'!'", "'~'", "'|'", "'+'", "';'", "'^'", "'.'", "'('", "')'", "'['", 
			"']'", "'{'", "'}'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "ASM_", "BREAK_", "CASE_", "CHAR_TYPE", "CONST_TYPE", "CONTINUE_", 
			"DEFAULT_", "DO_", "DOUBLE_TYPE", "ELSE_", "ENUM_", "EXTERN_TYPE", "FLOAT_TYPE", 
			"FOR_", "GOTO_", "IF_", "INT_TYPE", "LONG_TYPE", "PRAGMA_", "REGISTER_", 
			"RETURN_", "SHORT_TYPE", "SIGNED_TYPE", "SIZEOF_", "STATIC_", "STRUCT_", 
			"SWITCH_", "TYPEDEF_", "UNION_", "UNSIGNED_TYPE", "VOID_TYPE", "VOLATILE_TYPE", 
			"WHILE_", "INCLUDE_", "INCLUDE_LIB", "INCLUDE_OWN", "DEFINE_", "STRING", 
			"CHAR", "ID", "DEC_NUM", "FLOAT_NUM", "EQ_OP", "LE_OP", "GE_OP", "NE_OP", 
			"PP_OP", "MM_OP", "RSHIFT_OP", "LSHIFT_OP", "ASSIGN_OP", "AND_OP", "COLON", 
			"COMMA", "DIV_OP", "GT_OP", "LT_OP", "MINUS_OP", "MODULO_OP", "MULTI_OP_OR_POINTER", 
			"NOT_LOGIC_OP", "NOT_BITWISE_OP", "OR_OP", "PLUS_OP", "SEMICOLON", "XOR_OP", 
			"DOT", "LEFT_PAREM", "RIGHT_PAREM", "LEFT_BRACKET", "RIGHT_BRACKET", 
			"LEFT_BRACE", "RIGHT_BRACE", "COMMENT1", "COMMENT2", "WS", "NEW_LINE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public mylexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "mylexer.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	@Override
	public void action(RuleContext _localctx, int ruleIndex, int actionIndex) {
		switch (ruleIndex) {
		case 75:
			WS_action((RuleContext)_localctx, actionIndex);
			break;
		case 76:
			NEW_LINE_action((RuleContext)_localctx, actionIndex);
			break;
		}
	}
	private void WS_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 0:
			skip();
			break;
		}
	}
	private void NEW_LINE_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 1:
			skip();
			break;
		}
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2O\u023e\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G\tG\4H\tH\4I"+
		"\tI\4J\tJ\4K\tK\4L\tL\4M\tM\4N\tN\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3"+
		"\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t"+
		"\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\f\3\f"+
		"\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\16\3\16"+
		"\3\17\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\20\3\21\3\21\3\21\3\22\3\22"+
		"\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\24\3\24\3\24\3\24\3\24\3\24\3\24"+
		"\3\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\26\3\26\3\26\3\26"+
		"\3\26\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\3\30"+
		"\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\32\3\32\3\32\3\32\3\32"+
		"\3\32\3\32\3\33\3\33\3\33\3\33\3\33\3\33\3\33\3\34\3\34\3\34\3\34\3\34"+
		"\3\34\3\34\3\35\3\35\3\35\3\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\36"+
		"\3\36\3\36\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3 \3 \3 \3 \3"+
		" \3!\3!\3!\3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3"+
		"#\3#\3#\3#\3$\3$\6$\u0176\n$\r$\16$\u0177\3$\3$\3$\3$\3%\3%\6%\u0180\n"+
		"%\r%\16%\u0181\3%\3%\3%\3%\3&\3&\3&\3&\3&\3&\3&\3&\3\'\3\'\7\'\u0192\n"+
		"\'\f\'\16\'\u0195\13\'\3\'\3\'\3(\3(\7(\u019b\n(\f(\16(\u019e\13(\3(\3"+
		"(\3)\3)\7)\u01a4\n)\f)\16)\u01a7\13)\3*\7*\u01aa\n*\f*\16*\u01ad\13*\3"+
		"*\3*\3*\7*\u01b2\n*\f*\16*\u01b5\13*\5*\u01b7\n*\3+\7+\u01ba\n+\f+\16"+
		"+\u01bd\13+\3+\6+\u01c0\n+\r+\16+\u01c1\3+\3+\7+\u01c6\n+\f+\16+\u01c9"+
		"\13+\3+\3+\6+\u01cd\n+\r+\16+\u01ce\5+\u01d1\n+\3,\3,\3,\3-\3-\3-\3.\3"+
		".\3.\3/\3/\3/\3\60\3\60\3\60\3\61\3\61\3\61\3\62\3\62\3\62\3\63\3\63\3"+
		"\63\3\64\3\64\3\65\3\65\3\66\3\66\3\67\3\67\38\38\39\39\3:\3:\3;\3;\3"+
		"<\3<\3=\6=\u01fe\n=\r=\16=\u01ff\3>\3>\3?\3?\3@\3@\3A\3A\3B\3B\3C\3C\3"+
		"D\3D\3E\3E\3F\3F\3G\3G\3H\3H\3I\3I\3J\3J\3K\3K\3K\3K\7K\u0220\nK\fK\16"+
		"K\u0223\13K\3L\3L\3L\3L\7L\u0229\nL\fL\16L\u022c\13L\3L\3L\3L\3M\6M\u0232"+
		"\nM\rM\16M\u0233\3M\3M\3N\6N\u0239\nN\rN\16N\u023a\3N\3N\3\u022a\2O\3"+
		"\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37"+
		"\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37="+
		" ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67m8o9"+
		"q:s;u<w=y>{?}@\177A\u0081B\u0083C\u0085D\u0087E\u0089F\u008bG\u008dH\u008f"+
		"I\u0091J\u0093K\u0095L\u0097M\u0099N\u009bO\3\2\t\4\2\61\61c|\4\2\f\f"+
		"\17\17\5\2C\\aac|\6\2\62;C\\aac|\3\2\63;\3\2\62;\5\2\13\f\17\17\"\"\2"+
		"\u024f\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2"+
		"\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3"+
		"\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2"+
		"\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2"+
		"/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2"+
		"\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2"+
		"G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3"+
		"\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2"+
		"\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2"+
		"m\3\2\2\2\2o\3\2\2\2\2q\3\2\2\2\2s\3\2\2\2\2u\3\2\2\2\2w\3\2\2\2\2y\3"+
		"\2\2\2\2{\3\2\2\2\2}\3\2\2\2\2\177\3\2\2\2\2\u0081\3\2\2\2\2\u0083\3\2"+
		"\2\2\2\u0085\3\2\2\2\2\u0087\3\2\2\2\2\u0089\3\2\2\2\2\u008b\3\2\2\2\2"+
		"\u008d\3\2\2\2\2\u008f\3\2\2\2\2\u0091\3\2\2\2\2\u0093\3\2\2\2\2\u0095"+
		"\3\2\2\2\2\u0097\3\2\2\2\2\u0099\3\2\2\2\2\u009b\3\2\2\2\3\u009d\3\2\2"+
		"\2\5\u00a1\3\2\2\2\7\u00a7\3\2\2\2\t\u00ac\3\2\2\2\13\u00b1\3\2\2\2\r"+
		"\u00b7\3\2\2\2\17\u00c0\3\2\2\2\21\u00c8\3\2\2\2\23\u00cb\3\2\2\2\25\u00d2"+
		"\3\2\2\2\27\u00d7\3\2\2\2\31\u00dc\3\2\2\2\33\u00e3\3\2\2\2\35\u00e9\3"+
		"\2\2\2\37\u00ed\3\2\2\2!\u00f2\3\2\2\2#\u00f5\3\2\2\2%\u00f9\3\2\2\2\'"+
		"\u00fe\3\2\2\2)\u0106\3\2\2\2+\u010f\3\2\2\2-\u0116\3\2\2\2/\u011c\3\2"+
		"\2\2\61\u0123\3\2\2\2\63\u012a\3\2\2\2\65\u0131\3\2\2\2\67\u0138\3\2\2"+
		"\29\u013f\3\2\2\2;\u0147\3\2\2\2=\u014d\3\2\2\2?\u0156\3\2\2\2A\u015b"+
		"\3\2\2\2C\u0164\3\2\2\2E\u016a\3\2\2\2G\u0173\3\2\2\2I\u017d\3\2\2\2K"+
		"\u0187\3\2\2\2M\u018f\3\2\2\2O\u0198\3\2\2\2Q\u01a1\3\2\2\2S\u01ab\3\2"+
		"\2\2U\u01bb\3\2\2\2W\u01d2\3\2\2\2Y\u01d5\3\2\2\2[\u01d8\3\2\2\2]\u01db"+
		"\3\2\2\2_\u01de\3\2\2\2a\u01e1\3\2\2\2c\u01e4\3\2\2\2e\u01e7\3\2\2\2g"+
		"\u01ea\3\2\2\2i\u01ec\3\2\2\2k\u01ee\3\2\2\2m\u01f0\3\2\2\2o\u01f2\3\2"+
		"\2\2q\u01f4\3\2\2\2s\u01f6\3\2\2\2u\u01f8\3\2\2\2w\u01fa\3\2\2\2y\u01fd"+
		"\3\2\2\2{\u0201\3\2\2\2}\u0203\3\2\2\2\177\u0205\3\2\2\2\u0081\u0207\3"+
		"\2\2\2\u0083\u0209\3\2\2\2\u0085\u020b\3\2\2\2\u0087\u020d\3\2\2\2\u0089"+
		"\u020f\3\2\2\2\u008b\u0211\3\2\2\2\u008d\u0213\3\2\2\2\u008f\u0215\3\2"+
		"\2\2\u0091\u0217\3\2\2\2\u0093\u0219\3\2\2\2\u0095\u021b\3\2\2\2\u0097"+
		"\u0224\3\2\2\2\u0099\u0231\3\2\2\2\u009b\u0238\3\2\2\2\u009d\u009e\7c"+
		"\2\2\u009e\u009f\7u\2\2\u009f\u00a0\7o\2\2\u00a0\4\3\2\2\2\u00a1\u00a2"+
		"\7d\2\2\u00a2\u00a3\7t\2\2\u00a3\u00a4\7g\2\2\u00a4\u00a5\7c\2\2\u00a5"+
		"\u00a6\7m\2\2\u00a6\6\3\2\2\2\u00a7\u00a8\7e\2\2\u00a8\u00a9\7c\2\2\u00a9"+
		"\u00aa\7u\2\2\u00aa\u00ab\7g\2\2\u00ab\b\3\2\2\2\u00ac\u00ad\7e\2\2\u00ad"+
		"\u00ae\7j\2\2\u00ae\u00af\7c\2\2\u00af\u00b0\7t\2\2\u00b0\n\3\2\2\2\u00b1"+
		"\u00b2\7e\2\2\u00b2\u00b3\7q\2\2\u00b3\u00b4\7p\2\2\u00b4\u00b5\7u\2\2"+
		"\u00b5\u00b6\7v\2\2\u00b6\f\3\2\2\2\u00b7\u00b8\7e\2\2\u00b8\u00b9\7q"+
		"\2\2\u00b9\u00ba\7p\2\2\u00ba\u00bb\7v\2\2\u00bb\u00bc\7k\2\2\u00bc\u00bd"+
		"\7p\2\2\u00bd\u00be\7w\2\2\u00be\u00bf\7g\2\2\u00bf\16\3\2\2\2\u00c0\u00c1"+
		"\7f\2\2\u00c1\u00c2\7g\2\2\u00c2\u00c3\7h\2\2\u00c3\u00c4\7c\2\2\u00c4"+
		"\u00c5\7w\2\2\u00c5\u00c6\7n\2\2\u00c6\u00c7\7v\2\2\u00c7\20\3\2\2\2\u00c8"+
		"\u00c9\7f\2\2\u00c9\u00ca\7q\2\2\u00ca\22\3\2\2\2\u00cb\u00cc\7f\2\2\u00cc"+
		"\u00cd\7q\2\2\u00cd\u00ce\7w\2\2\u00ce\u00cf\7d\2\2\u00cf\u00d0\7n\2\2"+
		"\u00d0\u00d1\7g\2\2\u00d1\24\3\2\2\2\u00d2\u00d3\7g\2\2\u00d3\u00d4\7"+
		"n\2\2\u00d4\u00d5\7u\2\2\u00d5\u00d6\7g\2\2\u00d6\26\3\2\2\2\u00d7\u00d8"+
		"\7g\2\2\u00d8\u00d9\7p\2\2\u00d9\u00da\7w\2\2\u00da\u00db\7o\2\2\u00db"+
		"\30\3\2\2\2\u00dc\u00dd\7g\2\2\u00dd\u00de\7z\2\2\u00de\u00df\7v\2\2\u00df"+
		"\u00e0\7g\2\2\u00e0\u00e1\7t\2\2\u00e1\u00e2\7p\2\2\u00e2\32\3\2\2\2\u00e3"+
		"\u00e4\7h\2\2\u00e4\u00e5\7n\2\2\u00e5\u00e6\7q\2\2\u00e6\u00e7\7c\2\2"+
		"\u00e7\u00e8\7v\2\2\u00e8\34\3\2\2\2\u00e9\u00ea\7h\2\2\u00ea\u00eb\7"+
		"q\2\2\u00eb\u00ec\7t\2\2\u00ec\36\3\2\2\2\u00ed\u00ee\7i\2\2\u00ee\u00ef"+
		"\7q\2\2\u00ef\u00f0\7v\2\2\u00f0\u00f1\7q\2\2\u00f1 \3\2\2\2\u00f2\u00f3"+
		"\7k\2\2\u00f3\u00f4\7h\2\2\u00f4\"\3\2\2\2\u00f5\u00f6\7k\2\2\u00f6\u00f7"+
		"\7p\2\2\u00f7\u00f8\7v\2\2\u00f8$\3\2\2\2\u00f9\u00fa\7n\2\2\u00fa\u00fb"+
		"\7q\2\2\u00fb\u00fc\7p\2\2\u00fc\u00fd\7i\2\2\u00fd&\3\2\2\2\u00fe\u00ff"+
		"\7%\2\2\u00ff\u0100\7r\2\2\u0100\u0101\7t\2\2\u0101\u0102\7c\2\2\u0102"+
		"\u0103\7i\2\2\u0103\u0104\7o\2\2\u0104\u0105\7c\2\2\u0105(\3\2\2\2\u0106"+
		"\u0107\7t\2\2\u0107\u0108\7g\2\2\u0108\u0109\7i\2\2\u0109\u010a\7k\2\2"+
		"\u010a\u010b\7u\2\2\u010b\u010c\7v\2\2\u010c\u010d\7g\2\2\u010d\u010e"+
		"\7t\2\2\u010e*\3\2\2\2\u010f\u0110\7t\2\2\u0110\u0111\7g\2\2\u0111\u0112"+
		"\7v\2\2\u0112\u0113\7w\2\2\u0113\u0114\7t\2\2\u0114\u0115\7p\2\2\u0115"+
		",\3\2\2\2\u0116\u0117\7u\2\2\u0117\u0118\7j\2\2\u0118\u0119\7q\2\2\u0119"+
		"\u011a\7t\2\2\u011a\u011b\7v\2\2\u011b.\3\2\2\2\u011c\u011d\7u\2\2\u011d"+
		"\u011e\7k\2\2\u011e\u011f\7i\2\2\u011f\u0120\7p\2\2\u0120\u0121\7g\2\2"+
		"\u0121\u0122\7f\2\2\u0122\60\3\2\2\2\u0123\u0124\7u\2\2\u0124\u0125\7"+
		"k\2\2\u0125\u0126\7|\2\2\u0126\u0127\7g\2\2\u0127\u0128\7q\2\2\u0128\u0129"+
		"\7h\2\2\u0129\62\3\2\2\2\u012a\u012b\7u\2\2\u012b\u012c\7v\2\2\u012c\u012d"+
		"\7c\2\2\u012d\u012e\7v\2\2\u012e\u012f\7k\2\2\u012f\u0130\7e\2\2\u0130"+
		"\64\3\2\2\2\u0131\u0132\7u\2\2\u0132\u0133\7v\2\2\u0133\u0134\7t\2\2\u0134"+
		"\u0135\7w\2\2\u0135\u0136\7e\2\2\u0136\u0137\7v\2\2\u0137\66\3\2\2\2\u0138"+
		"\u0139\7u\2\2\u0139\u013a\7y\2\2\u013a\u013b\7k\2\2\u013b\u013c\7v\2\2"+
		"\u013c\u013d\7e\2\2\u013d\u013e\7j\2\2\u013e8\3\2\2\2\u013f\u0140\7v\2"+
		"\2\u0140\u0141\7{\2\2\u0141\u0142\7r\2\2\u0142\u0143\7g\2\2\u0143\u0144"+
		"\7f\2\2\u0144\u0145\7g\2\2\u0145\u0146\7h\2\2\u0146:\3\2\2\2\u0147\u0148"+
		"\7w\2\2\u0148\u0149\7p\2\2\u0149\u014a\7k\2\2\u014a\u014b\7q\2\2\u014b"+
		"\u014c\7p\2\2\u014c<\3\2\2\2\u014d\u014e\7w\2\2\u014e\u014f\7p\2\2\u014f"+
		"\u0150\7u\2\2\u0150\u0151\7k\2\2\u0151\u0152\7i\2\2\u0152\u0153\7p\2\2"+
		"\u0153\u0154\7g\2\2\u0154\u0155\7f\2\2\u0155>\3\2\2\2\u0156\u0157\7x\2"+
		"\2\u0157\u0158\7q\2\2\u0158\u0159\7k\2\2\u0159\u015a\7f\2\2\u015a@\3\2"+
		"\2\2\u015b\u015c\7x\2\2\u015c\u015d\7q\2\2\u015d\u015e\7n\2\2\u015e\u015f"+
		"\7c\2\2\u015f\u0160\7v\2\2\u0160\u0161\7k\2\2\u0161\u0162\7n\2\2\u0162"+
		"\u0163\7g\2\2\u0163B\3\2\2\2\u0164\u0165\7y\2\2\u0165\u0166\7j\2\2\u0166"+
		"\u0167\7k\2\2\u0167\u0168\7n\2\2\u0168\u0169\7g\2\2\u0169D\3\2\2\2\u016a"+
		"\u016b\7%\2\2\u016b\u016c\7k\2\2\u016c\u016d\7p\2\2\u016d\u016e\7e\2\2"+
		"\u016e\u016f\7n\2\2\u016f\u0170\7w\2\2\u0170\u0171\7f\2\2\u0171\u0172"+
		"\7g\2\2\u0172F\3\2\2\2\u0173\u0175\7>\2\2\u0174\u0176\t\2\2\2\u0175\u0174"+
		"\3\2\2\2\u0176\u0177\3\2\2\2\u0177\u0175\3\2\2\2\u0177\u0178\3\2\2\2\u0178"+
		"\u0179\3\2\2\2\u0179\u017a\7\60\2\2\u017a\u017b\7j\2\2\u017b\u017c\7@"+
		"\2\2\u017cH\3\2\2\2\u017d\u017f\7$\2\2\u017e\u0180\t\2\2\2\u017f\u017e"+
		"\3\2\2\2\u0180\u0181\3\2\2\2\u0181\u017f\3\2\2\2\u0181\u0182\3\2\2\2\u0182"+
		"\u0183\3\2\2\2\u0183\u0184\7\60\2\2\u0184\u0185\7j\2\2\u0185\u0186\7$"+
		"\2\2\u0186J\3\2\2\2\u0187\u0188\7%\2\2\u0188\u0189\7f\2\2\u0189\u018a"+
		"\7g\2\2\u018a\u018b\7h\2\2\u018b\u018c\7k\2\2\u018c\u018d\7p\2\2\u018d"+
		"\u018e\7g\2\2\u018eL\3\2\2\2\u018f\u0193\7$\2\2\u0190\u0192\n\3\2\2\u0191"+
		"\u0190\3\2\2\2\u0192\u0195\3\2\2\2\u0193\u0191\3\2\2\2\u0193\u0194\3\2"+
		"\2\2\u0194\u0196\3\2\2\2\u0195\u0193\3\2\2\2\u0196\u0197\7$\2\2\u0197"+
		"N\3\2\2\2\u0198\u019c\7)\2\2\u0199\u019b\n\3\2\2\u019a\u0199\3\2\2\2\u019b"+
		"\u019e\3\2\2\2\u019c\u019a\3\2\2\2\u019c\u019d\3\2\2\2\u019d\u019f\3\2"+
		"\2\2\u019e\u019c\3\2\2\2\u019f\u01a0\7)\2\2\u01a0P\3\2\2\2\u01a1\u01a5"+
		"\t\4\2\2\u01a2\u01a4\t\5\2\2\u01a3\u01a2\3\2\2\2\u01a4\u01a7\3\2\2\2\u01a5"+
		"\u01a3\3\2\2\2\u01a5\u01a6\3\2\2\2\u01a6R\3\2\2\2\u01a7\u01a5\3\2\2\2"+
		"\u01a8\u01aa\7/\2\2\u01a9\u01a8\3\2\2\2\u01aa\u01ad\3\2\2\2\u01ab\u01a9"+
		"\3\2\2\2\u01ab\u01ac\3\2\2\2\u01ac\u01b6\3\2\2\2\u01ad\u01ab\3\2\2\2\u01ae"+
		"\u01b7\7\62\2\2\u01af\u01b3\t\6\2\2\u01b0\u01b2\t\7\2\2\u01b1\u01b0\3"+
		"\2\2\2\u01b2\u01b5\3\2\2\2\u01b3\u01b1\3\2\2\2\u01b3\u01b4\3\2\2\2\u01b4"+
		"\u01b7\3\2\2\2\u01b5\u01b3\3\2\2\2\u01b6\u01ae\3\2\2\2\u01b6\u01af\3\2"+
		"\2\2\u01b7T\3\2\2\2\u01b8\u01ba\7/\2\2\u01b9\u01b8\3\2\2\2\u01ba\u01bd"+
		"\3\2\2\2\u01bb\u01b9\3\2\2\2\u01bb\u01bc\3\2\2\2\u01bc\u01d0\3\2\2\2\u01bd"+
		"\u01bb\3\2\2\2\u01be\u01c0\t\7\2\2\u01bf\u01be\3\2\2\2\u01c0\u01c1\3\2"+
		"\2\2\u01c1\u01bf\3\2\2\2\u01c1\u01c2\3\2\2\2\u01c2\u01c3\3\2\2\2\u01c3"+
		"\u01c7\7\60\2\2\u01c4\u01c6\t\7\2\2\u01c5\u01c4\3\2\2\2\u01c6\u01c9\3"+
		"\2\2\2\u01c7\u01c5\3\2\2\2\u01c7\u01c8\3\2\2\2\u01c8\u01d1\3\2\2\2\u01c9"+
		"\u01c7\3\2\2\2\u01ca\u01cc\7\60\2\2\u01cb\u01cd\t\7\2\2\u01cc\u01cb\3"+
		"\2\2\2\u01cd\u01ce\3\2\2\2\u01ce\u01cc\3\2\2\2\u01ce\u01cf\3\2\2\2\u01cf"+
		"\u01d1\3\2\2\2\u01d0\u01bf\3\2\2\2\u01d0\u01ca\3\2\2\2\u01d1V\3\2\2\2"+
		"\u01d2\u01d3\7?\2\2\u01d3\u01d4\7?\2\2\u01d4X\3\2\2\2\u01d5\u01d6\7>\2"+
		"\2\u01d6\u01d7\7?\2\2\u01d7Z\3\2\2\2\u01d8\u01d9\7@\2\2\u01d9\u01da\7"+
		"?\2\2\u01da\\\3\2\2\2\u01db\u01dc\7#\2\2\u01dc\u01dd\7?\2\2\u01dd^\3\2"+
		"\2\2\u01de\u01df\7-\2\2\u01df\u01e0\7-\2\2\u01e0`\3\2\2\2\u01e1\u01e2"+
		"\7/\2\2\u01e2\u01e3\7/\2\2\u01e3b\3\2\2\2\u01e4\u01e5\7>\2\2\u01e5\u01e6"+
		"\7>\2\2\u01e6d\3\2\2\2\u01e7\u01e8\7@\2\2\u01e8\u01e9\7@\2\2\u01e9f\3"+
		"\2\2\2\u01ea\u01eb\7?\2\2\u01ebh\3\2\2\2\u01ec\u01ed\7(\2\2\u01edj\3\2"+
		"\2\2\u01ee\u01ef\7<\2\2\u01efl\3\2\2\2\u01f0\u01f1\7.\2\2\u01f1n\3\2\2"+
		"\2\u01f2\u01f3\7\61\2\2\u01f3p\3\2\2\2\u01f4\u01f5\7@\2\2\u01f5r\3\2\2"+
		"\2\u01f6\u01f7\7>\2\2\u01f7t\3\2\2\2\u01f8\u01f9\7/\2\2\u01f9v\3\2\2\2"+
		"\u01fa\u01fb\7\'\2\2\u01fbx\3\2\2\2\u01fc\u01fe\7,\2\2\u01fd\u01fc\3\2"+
		"\2\2\u01fe\u01ff\3\2\2\2\u01ff\u01fd\3\2\2\2\u01ff\u0200\3\2\2\2\u0200"+
		"z\3\2\2\2\u0201\u0202\7#\2\2\u0202|\3\2\2\2\u0203\u0204\7\u0080\2\2\u0204"+
		"~\3\2\2\2\u0205\u0206\7~\2\2\u0206\u0080\3\2\2\2\u0207\u0208\7-\2\2\u0208"+
		"\u0082\3\2\2\2\u0209\u020a\7=\2\2\u020a\u0084\3\2\2\2\u020b\u020c\7`\2"+
		"\2\u020c\u0086\3\2\2\2\u020d\u020e\7\60\2\2\u020e\u0088\3\2\2\2\u020f"+
		"\u0210\7*\2\2\u0210\u008a\3\2\2\2\u0211\u0212\7+\2\2\u0212\u008c\3\2\2"+
		"\2\u0213\u0214\7]\2\2\u0214\u008e\3\2\2\2\u0215\u0216\7_\2\2\u0216\u0090"+
		"\3\2\2\2\u0217\u0218\7}\2\2\u0218\u0092\3\2\2\2\u0219\u021a\7\177\2\2"+
		"\u021a\u0094\3\2\2\2\u021b\u021c\7\61\2\2\u021c\u021d\7\61\2\2\u021d\u0221"+
		"\3\2\2\2\u021e\u0220\n\3\2\2\u021f\u021e\3\2\2\2\u0220\u0223\3\2\2\2\u0221"+
		"\u021f\3\2\2\2\u0221\u0222\3\2\2\2\u0222\u0096\3\2\2\2\u0223\u0221\3\2"+
		"\2\2\u0224\u0225\7\61\2\2\u0225\u0226\7,\2\2\u0226\u022a\3\2\2\2\u0227"+
		"\u0229\13\2\2\2\u0228\u0227\3\2\2\2\u0229\u022c\3\2\2\2\u022a\u022b\3"+
		"\2\2\2\u022a\u0228\3\2\2\2\u022b\u022d\3\2\2\2\u022c\u022a\3\2\2\2\u022d"+
		"\u022e\7,\2\2\u022e\u022f\7\61\2\2\u022f\u0098\3\2\2\2\u0230\u0232\t\b"+
		"\2\2\u0231\u0230\3\2\2\2\u0232\u0233\3\2\2\2\u0233\u0231\3\2\2\2\u0233"+
		"\u0234\3\2\2\2\u0234\u0235\3\2\2\2\u0235\u0236\bM\2\2\u0236\u009a\3\2"+
		"\2\2\u0237\u0239\7\f\2\2\u0238\u0237\3\2\2\2\u0239\u023a\3\2\2\2\u023a"+
		"\u0238\3\2\2\2\u023a\u023b\3\2\2\2\u023b\u023c\3\2\2\2\u023c\u023d\bN"+
		"\3\2\u023d\u009c\3\2\2\2\25\2\u0177\u0181\u0193\u019c\u01a5\u01ab\u01b3"+
		"\u01b6\u01bb\u01c1\u01c7\u01ce\u01d0\u01ff\u0221\u022a\u0233\u023a\4\3"+
		"M\2\3N\3";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}