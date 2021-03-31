#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define STACKSIZE 4096

char opstack[STACKSIZE];
short optop = 0;

void push(char);
char pop();
bool is_operator(char);
short precedence(char symbol);
void in2post(char *infix, char *postfix);


///////////////////////////////////////////////////////////////////
int main() {
	char infix[STACKSIZE], postfix[STACKSIZE];
    memset(infix, 0, sizeof(char) * STACKSIZE);

    while (fgets(infix, STACKSIZE, stdin) != NULL) {
        if (infix[strlen(infix) - 1] == '\n') {
            infix[strlen(infix) - 1] = '\0';
        }
        memset(postfix, 0, sizeof(char) * STACKSIZE);

        in2post(infix,postfix);

        printf("%s\n", postfix);
    }

	return 0;
}
///////////////////////////////////////////////////////////////////

void push(char op) {
	opstack[optop++] = op;
}

char pop() {
	char op;

	op = opstack[--optop];
	return op;
}

bool is_operator(char symbol) {
	if(symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-') {
		return true;
	} else {
	    return false;
	}
}

short precedence(char symbol) { // higher integer value means higher precendence.
	if(symbol == '*' || symbol == '/') {
		return 1;
	} else if(symbol == '+' || symbol == '-') {
		return 0;
	} else {
		return -1;
	}
}

void in2post(char *infix, char *postfix) { 
    char *infixptr;
    char *postfixptr;
	char item;
	char operator;
    bool hp, iw;  // higher precendence, in word

	push('(');
	strcat(infix, ")");

    infixptr = infix;
    postfixptr = postfix;

	while (*infixptr) {
        item = *infixptr;
		if (*infixptr == '(') {
			push(*infixptr);
		} else if ( isdigit(*infixptr) || isalpha(*infixptr) || *infixptr == '.' ) {
			*postfixptr++ = *infixptr;
            iw = true;
		} else if (is_operator(item)) {
            hp = false;
			operator = pop();
			while ( is_operator(operator) && (precedence(operator) >= precedence(item)) ) {
                hp = true;
                if (iw) {
                    *postfixptr++ = ' ';
                    iw = false;
                }
				*postfixptr++ = operator;  // pop all higher precendence operator.
				*postfixptr++ = ' ';
                operator = pop();  // add them to postfix expresion
			}
			push(operator);  // if the loop is out, then this operator must be stored back to stack
			push(*infixptr);
            if (!hp) {
                *postfixptr++ = ' ';
            }
		} else if (*infixptr == ')') {
			while((operator = pop()) != '(') {
                *postfixptr++ = ' ';
				*postfixptr++ = operator;
			}
		} else {
			exit(1);
		}
		++infixptr;
	}

	if (optop > 0) {
		exit(1);
	}

	*postfixptr = '\0';
}