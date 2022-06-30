grammar Calc;

options {
	language=C;
}

@header {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

@members {
/** Map variable name to Integer object holding value */
// variable name can only have one char.
// Access method is: HashMap[variable_name - 'A']
int HashMap[26];
}

prog:   state+ ;
                
state:   expr NEWLINE { printf("\%d\n", $expr.value);}
    |   ID '=' expr NEWLINE
        {char tmp[10];
         strcpy(tmp, (char*)$ID.text->chars);
         HashMap[tmp[0]-'A'] = $expr.value;}
    |   NEWLINE
    ;

expr returns [int value]
    :   e=multExpr {$value = $e.value;}
        (   '+' e=multExpr {$value += $e.value;}
        |   '-' e=multExpr {$value -= $e.value;}
        )*
    ;

multExpr returns [int value]
    :   e=atom {$value = $e.value;} ('*' e=atom {$value *= $e.value;})*
    ; 

atom returns [int value]
    :   INT {$value = atoi((char*)$INT.text->chars); printf("\%d  \%s\n", $value, (char*)$INT.text->chars);}
    |   ID
        {
        char tmp[10];
        strcpy(tmp, (char*)$ID.text->chars);
        int v = HashMap[tmp[0]-'A'];
        if ( v!=0 ) $value = v;
        else printf("undefined variable \%s\n", (char*)$ID.text->chars);
        }
    |   '(' expr ')' {$value = $expr.value;}
    ;

ID  :   ('a'..'z'|'A'..'Z')+ ;
INT :   '0'..'9'+ ;
NEWLINE:'\r'? '\n' ;
WS  :   (' '|'\t')+ {$channel=HIDDEN;};
