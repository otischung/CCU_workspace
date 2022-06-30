grammar myparser;

options {
	language = Java;
}

@header {
    // import packages here. (depends on language)
}

@members {  // you can treat it as global variable.
    boolean TRACEON = true;
}

// program: INT_TYPE MAIN_FUNC '(' ')' '{' declarations statements '}' { if (TRACEON) {
// System.out.println("INT_TYPE MAIN_FUNC () {declarations statements}"); } };

// declarations: type ID ';' declarations { if (TRACEON) { System.out.println("declarations: type ID
// ; declarations"); } } | { if (TRACEON) { System.out.println("declarations: epsilon"); } };

// type: INT_TYPE { if (TRACEON) { System.out.println("type: INT_TYPE"); } } | FLOAT_TYPE { if
// (TRACEON) { System.out.println("type: FLOAT_TYPE"); } } | DOUBLE_TYPE { if (TRACEON) {
// System.out.println("type: DOUBLE_TYPE"); } } | CHAR_TYPE { if (TRACEON) {
// System.out.println("type: CHAR_TYPE"); } };

translationUnit:
	externalDeclaration
	| translationUnit externalDeclaration
	| INCLUDE_ (INCLUDE_LIB | INCLUDE_OWN) {
		if (TRACEON) {
			System.out.println("INCLUDE_ (INCLUDE_LIB | INCLUDE_OWN)");
		}
	};

externalDeclaration:
	functionDefinition {
		if (TRACEON) {
			System.out.println("A function is defined here.");
		}
	}
	| declaration {
		if (TRACEON) {
			System.out.println("A declaration is defined here.");
		}
	};

functionDefinition:
	declarationSpecifiers declarator declarationList compoundStatement
	| declarationSpecifiers declarator compoundStatement;
	// | declarator declarationList compoundStatement // NOT in GNU C99
	// | declarator compoundStatement; // NOT in GNU C99

declarationList: declaration | declarationList declaration;

primaryExpr:
	ID
	| DEC_NUM
	| FLOAT_NUM
	| STRING
	| CHAR
	| '(' expr ')';

postfixExpr:
	PRINTF '(' argumentExprList ')' {
		if (TRACEON) {
			System.out.println("function printf is declared here.");
		}
	}
	| primaryExpr
	| postfixExpr '[' expr ']'
	| postfixExpr '(' ')'
	| postfixExpr '(' argumentExprList ')'
	| postfixExpr '.' ID
	| postfixExpr POINTER_OP ID
	| postfixExpr INC_OP
	| postfixExpr DEC_OP
	| '(' typeName ')' '{' initializerList '}' // GNU_C99
	| '(' typeName ')' '{' initializerList ',' '}'; // GNU_C99

argumentExprList: assignExpr | argumentExprList ',' assignExpr;

unaryExpr:
	postfixExpr
	| INC_OP unaryExpr // GNU_C99
	| DEC_OP unaryExpr // GNU_C99
	| unaryOP castExpr
	| SIZEOF_ unaryExpr
	| SIZEOF_ '(' typeName ')';

unaryOP: '&' | '*' | '+' | '-' | '~' | '!';

castExpr: unaryExpr | '(' typeName ')' castExpr;

multiplicativeExpr:
	castExpr
	| multiplicativeExpr '*' castExpr
	| multiplicativeExpr '/' castExpr
	| multiplicativeExpr '%' castExpr;

additiveExpr:
	multiplicativeExpr
	| additiveExpr '+' multiplicativeExpr
	| additiveExpr '-' multiplicativeExpr;

shiftExpr:
	additiveExpr
	| shiftExpr RSHIFT_OP multiplicativeExpr
	| shiftExpr LSHIFT_OP multiplicativeExpr;

relationalExpr:
	shiftExpr
	| relationalExpr LT_OP shiftExpr
	| relationalExpr GT_OP shiftExpr
	| relationalExpr LE_OP shiftExpr
	| relationalExpr GE_OP shiftExpr;

equalityExpr:
	relationalExpr
	| equalityExpr EQ_OP relationalExpr
	| equalityExpr NE_OP relationalExpr;

andExpr: equalityExpr | andExpr '&' equalityExpr;

xorExpr: andExpr | xorExpr '^' andExpr;

orExpr: xorExpr | orExpr '|' xorExpr;

logicAndExpr: orExpr | logicAndExpr AND_OP orExpr;

logicOrExpr: logicAndExpr | logicOrExpr OR_OP orExpr;

conditionExpr:
	logicOrExpr
	| logicOrExpr '?' expr ':' conditionExpr;

assignExpr: conditionExpr | unaryExpr assignOP assignExpr;

assignOP:
	'='
	| RIGHT_ASSIGN
	| LEFT_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| AND_ASSIGN
	| OR_ASSIGN
	| XOR_ASSIGN;

expr: assignExpr | expr ',' assignExpr;

declaration:
	declarationSpecifiers ';'
	| declarationSpecifiers initDeclaratorList ';';

declarationSpecifiers:
	storageClassSpecifier
	| storageClassSpecifier declarationSpecifiers
	| typeSpecifier
	| typeSpecifier declarationSpecifiers
	| typeQuantifier
	| typeQuantifier declarationSpecifiers;

initDeclaratorList:
	initDeclarator
	| initDeclaratorList ',' initDeclarator;

initDeclarator: declarator | declarator '=' initializer;

storageClassSpecifier:
	TYPEDEF_
	| EXTERN_TYPE
	| STATIC_
	| REGISTER_;

typeSpecifier:
	VOID_TYPE
	| CHAR_TYPE
	| SHORT_TYPE
	| INT_TYPE
	| LONG_TYPE
	| FLOAT_TYPE
	| DOUBLE_TYPE
	| SIGNED_TYPE
	| UNSIGNED_TYPE
	| structOrUnionSpecifier
	| enumSpecifier;

typeQuantifier: CONST_TYPE | VOLATILE_TYPE;

structOrUnion: STRUCT_ | UNION_;

structOrUnionSpecifier:
	structOrUnion ID '{' structDeclarationList '}'
	// | structOrUnion ID '{' '}'  // New define
	| structOrUnion '{' structDeclarationList '}'
	| structOrUnion ID;

structDeclarationList:
	structDeclaration
	| structDeclarationList structDeclaration
	|;  // New define

structDeclaration:
	specifierQuantifierList structDeclaratorList ';';

specifierQuantifierList:
	typeSpecifier
	| typeSpecifier specifierQuantifierList
	| typeQuantifier
	| typeQuantifier specifierQuantifierList;

structDeclaratorList:
	structDeclarator
	| structDeclaratorList ',' structDeclarator;

structDeclarator:
	declarator
	| ':' conditionExpr
	| declarator ':' conditionExpr;

enumSpecifier:
	ENUM_ '{' enumeratorList '}'
	| ENUM_ ID '{' enumeratorList '}'
	| ENUM_ '{' enumeratorList ',' '}'
	| ENUM_ ID '{' enumeratorList ',' '}'
	| ENUM_ ID;

enumeratorList: enumerator | enumeratorList ',' enumerator;

enumerator: ID | ID '=' conditionExpr;

declarator: pointer directDeclarator | directDeclarator;

directDeclarator:
	ID
	| '(' declarator ')'
	| directDeclarator '[' typeQuantifierList assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList ']' // GNU C99
	| directDeclarator '[' assignExpr ']' // GNU C99
	| directDeclarator '[' STATIC_ typeQuantifierList assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList STATIC_ assignExpr ']' // GNU C99
	| directDeclarator '[' typeQuantifierList '*' ']' // GNU C99
	// | directDeclarator '[' conditionExpr ']' // NOT in GNU C99
	| directDeclarator '[' '*' ']' // GNU C99
	| directDeclarator '[' ']'
	| directDeclarator '(' parameterTypeList ')'
	| directDeclarator '(' idList ')'
	| directDeclarator '(' ')';

pointer:
	'*'
	| '*' typeQuantifierList
	| '*' pointer
	| '*' typeQuantifierList pointer;

typeQuantifierList:
	typeQuantifier
	| typeQuantifierList typeQuantifier;

parameterTypeList: | parameterList | parameterList ',' '...';

parameterList:
	parameterDeclaration
	| parameterList ',' parameterDeclaration;

parameterDeclaration:
	declarationSpecifiers declarator
	| declarationSpecifiers abstractDeclarator
	| declarationSpecifiers;

idList: ID | idList ',' ID;

typeName: specifierQuantifierList | specifierQuantifierList abstractDeclarator;

abstractDeclarator:
	pointer
	| directAbstractDeclarator
	| pointer directAbstractDeclarator;

directAbstractDeclarator:
	'(' abstractDeclarator ')'
	| '[' ']'
	| '[' assignExpr ']' // GNU C99
	// | '[' conditionExpr ']' // NOT in GNU C99
	| directAbstractDeclarator '[' ']'
	| directAbstractDeclarator '[' assignExpr ']' // GNU C99
	// | directAbstractDeclarator '[' conditionExpr ']' // NOT in GNU C99
	| '[' '*' ']' // GNU C99
	| '(' ')'
	| '(' parameterTypeList ')'
	| directAbstractDeclarator '(' ')'
	| directAbstractDeclarator '(' parameterTypeList ')';

initializer:
	assignExpr
	| '{' initializerList '}'
	| '{' initializerList ',' '}';

// initializerList: initializer | initializerList ',' initializer;

initializerList:
	initializer
	| designation initializer  // GNU C99
	| initializerList ',' initializer
	| initializerList ',' designation initializer;  // GNU C99

designation: designatorList '=';  // GNU C99

designatorList: designator | designatorList designator;  // GNU C99

designator: '[' conditionExpr ']' | '.' ID;  // GNU C99

statement:
	labeledStatement
	| compoundStatement
	| exprStatement
	| selectionStatement
	| iterationStatement
	| jumpStatement;

labeledStatement:
	ID ':' statement
	| CASE_ conditionExpr ':' statement
	| DEFAULT_ ':' statement;

// ----- ASCI C -----
// compoundStatement:
// 	'{' '}'
// 	| '{' statementList '}'
// 	| '{' declarationList '}'
// 	| '{' declarationList statementList '}';

// statementList: statement | statementList statement;
// ----- ASCI C -----

// ----- GNU C99 -----
compoundStatement:
	'{' '}'
	| '{' blockItemList '}';

blockItemList: blockItem | blockItemList blockItem;

blockItem: declaration | statement;
// ----- GNU C99 -----

exprStatement: ';' | expr ';';

selectionStatement:
	IF_ '(' expr ')' statement {
		if (TRACEON) {
			System.out.println("An IF statement is declared here.");
		}
	}
	| IF_ '(' expr ')' statement ELSE_ statement {
		if (TRACEON) {
			System.out.println("An IF_ELSE statement is declared here.");
		}
	}
	| SWITCH_ '(' expr ')' statement {
		if (TRACEON) {
			System.out.println("A SWITCH_CASE statement is declared here.");
		}
	};

iterationStatement:
	WHILE_ '(' expr ')' statement {
		if (TRACEON) {
			System.out.println("A WHILE statement is declared here.");
		}
	}
	| DO_ statement WHILE_ '(' expr ')' ';' {
		if (TRACEON) {
			System.out.println("A DO_WHILE statement is declared here.");
		}
	}
	| FOR_ '(' exprStatement exprStatement ')' statement {
		if (TRACEON) {
			System.out.println("A FOR statement is declared here.");
		}
	}
	| FOR_ '(' exprStatement exprStatement expr ')' statement {
		if (TRACEON) {
			System.out.println("A FOR statement is declared here.");
		}
	}
	// GNU C99
	| FOR_ '(' declaration exprStatement ')' statement {
		if (TRACEON) {
			System.out.println("A GNU C99 FOR statement is declared here.");
		}
	}
	// GNU C99
	| FOR_ '(' declaration exprStatement expr ')' statement {
		if (TRACEON) {
			System.out.println("A GNU C99 FOR statement is declared here.");
		}
	};

jumpStatement:
	GOTO_ ID ';'
	| CONTINUE_ ';'
	| BREAK_ ';'
	| RETURN_ ';'
	| RETURN_ expr ';';

// ------ Lexer ------

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

/*----------------------*/
/*    Some Functions    */
/*----------------------*/
PRINTF: 'printf';

// fragment LETTER: 'a' .. 'z' | 'A' .. 'Z' | '_'; fragment DIGIT: '0' ..'9';

INCLUDE_: '#include';
INCLUDE_LIB: '<' [a-z/]+ '.h>';
INCLUDE_OWN: '"' [a-z/]+ '.h"';
DEFINE_: '#define';
STRING: '"' ~["\r\n]* '"';
CHAR: '\'' ~['\r\n]* '\'';

ID: [a-zA-Z_][a-zA-Z0-9_]*;
DEC_NUM: '0' | [1-9][0-9]*;
FLOAT_NUM: [0-9]+ '.' [0-9]* | '.' [0-9]+;

/*----------------------*/
/*   Assign Operators   */
/*----------------------*/
RIGHT_ASSIGN: '>>=';
LEFT_ASSIGN: '<<=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';

/*----------------------*/
/*  Compound Operators  */
/*----------------------*/

AND_OP: '&&';
EQ_OP: '==';
LE_OP: '<=';
GE_OP: '>=';
NE_OP: '!=';
INC_OP: '++';
DEC_OP: '--';
OR_OP: '||';
RSHIFT_OP: '<<';
LSHIFT_OP: '>>';
POINTER_OP: '->';

/*----------------------*/
/*   Single Operators   */
/*----------------------*/

ASSIGN_OP: '=';
DIV_OP: '/';
GT_OP: '>';
LT_OP: '<';
MINUS_OP: '-';
MODULO_OP: '%';
NOT_LOGIC_OP: '!';
NOT_BITWISE_OP: '~';
PLUS_OP: '+';
XOR_OP: '^';

COLON: ':';
COMMA: ',';
MULTI_OP_OR_POINTER: '*'+;
SEMICOLON: ';';
DOT: '.';
LEFT_PAREM: '(';
RIGHT_PAREM: ')';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';

WS: [ \r\n\t]+ -> channel(HIDDEN);
// WS: [ \r\n\t]+ {skip();}; WS: (' ' | '\r' | '\n' | '\t')+ {skip();};
NEW_LINE: '\n'+ {skip();};

/* Comments */
COMMENT1: '//' ~[\r\n]* -> skip;
COMMENT2: '/*' .*? '*/' -> skip;
// COMMENT2: '/*' (options {greedy = false;}: .)* '*/';

// https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// https://gist.github.com/codebrainz/2933703
