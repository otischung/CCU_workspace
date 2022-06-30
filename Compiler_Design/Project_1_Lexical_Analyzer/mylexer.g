lexer grammar mylexer;

options {
	language = Java;
}

/*----------------------*/
/*   Reserved Keywords  */
/*----------------------*/
ASM_: 'asm';
BREAK_: 'break';
CASE_: 'case';
CHAR_TYPE: 'char';
CONST_TYPE: 'const';
CONTINUE_: 'continue';
DEFAULT_: 'default';
DO_: 'do';
DOUBLE_TYPE: 'double';
ELSE_: 'else';
ENUM_: 'enum';
EXTERN_TYPE: 'extern';
FLOAT_TYPE: 'float';
FOR_: 'for';
GOTO_: 'goto';
IF_: 'if';
INT_TYPE: 'int';
LONG_TYPE: 'long';
PRAGMA_: '#pragma';
REGISTER_: 'register';
RETURN_: 'return';
SHORT_TYPE: 'short';
SIGNED_TYPE: 'signed';
SIZEOF_: 'sizeof';
STATIC_: 'static';
STRUCT_: 'struct';
SWITCH_: 'switch';
TYPEDEF_: 'typedef';
UNION_: 'union';
UNSIGNED_TYPE: 'unsigned';
VOID_TYPE: 'void';
VOLATILE_TYPE: 'volatile';
WHILE_: 'while';

// fragment LETTER: 'a' .. 'z' | 'A' .. 'Z' | '_';
// fragment DIGIT: '0' ..'9';

INCLUDE_: '#include';
INCLUDE_LIB: '<' [a-z/]+ '.h>';
INCLUDE_OWN: '"' [a-z/]+ '.h"';
DEFINE_: '#define';
STRING: '"' ~[\r\n]* '"';
CHAR: '\'' ~[\r\n]* '\'';

ID: [a-zA-Z_][a-zA-Z0-9_]*;
DEC_NUM: '-'* ('0' | [1-9][0-9]*);
FLOAT_NUM: '-'* ([0-9]+'.'[0-9]* | '.'[0-9]+);

/*----------------------*/
/*  Compound Operators  */
/*----------------------*/

EQ_OP: '==';
LE_OP: '<=';
GE_OP: '>=';
NE_OP: '!=';
PP_OP: '++';
MM_OP: '--';
RSHIFT_OP: '<<';
LSHIFT_OP: '>>';

/*----------------------*/
/*   Single Operators   */
/*----------------------*/

ASSIGN_OP: '=';
AND_OP: '&';
COLON: ':';
COMMA: ',';
DIV_OP: '/';
GT_OP: '>';
LT_OP: '<';
MINUS_OP: '-';
MODULO_OP: '%';
MULTI_OP_OR_POINTER: '*'+;
NOT_LOGIC_OP: '!';
NOT_BITWISE_OP: '~';
OR_OP: '|';
PLUS_OP: '+';
SEMICOLON: ';';
XOR_OP: '^';
DOT: '.';

LEFT_PAREM: '(';
RIGHT_PAREM: ')';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';

/* Comments */
COMMENT1: '//' ~[\r\n]*;
COMMENT2: '/*' .*? '*/';
// COMMENT2: '/*' (options {greedy = false;}: .)* '*/';

WS: [ \r\n\t]+ {skip();};
// WS: (' ' | '\r' | '\n' | '\t')+ {skip();};
NEW_LINE: '\n'+ {skip();};
