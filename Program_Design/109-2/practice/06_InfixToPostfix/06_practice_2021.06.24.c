#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define STACKSIZE 4096

/*                   stack maintainance                   */
typedef struct STACK {
    char arr[STACKSIZE];
    int cnt;
} Stack;
void stack_init(Stack *s);
void stack_push(Stack *s, char c);
char stack_pop(Stack *s);
void stack_print(Stack *s);
/***********************************************************/

bool is_operator(char c);
short precedence(char c);
void in2post(Stack *s, char *input, char *output);


/////////////////////////////////////////////////////////////
int main() {
    Stack s;
    char input[4096], output[4096];
    
    stack_init(&s);

    while (fgets(input, 4096, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        in2post(&s, input, output);
        printf("%s\n", output);
    }
    
    return 0;
}
/////////////////////////////////////////////////////////////


/*                   stack maintainance                   */
void stack_init(Stack *s) {
    s->cnt = 0;
}

void stack_push(Stack *s, char c) {
    if (s->cnt == STACKSIZE) {
        fprintf(stderr, "stack is full.\n");
        return;
    }
    s->arr[s->cnt++] = c;
}

char stack_pop(Stack *s) {
    if (s->cnt == 0) {
        fprintf(stderr, "stack is empty.\n");
        return -1;
    }
    return s->arr[--(s->cnt)];
}

void stack_print(Stack *s) {
    for (int i = 0; i < s->cnt; ++i) {
        printf("%c%c", s->arr[i], " \n"[i == s->cnt - 1]);
    }
    printf("s->cnt = %d\n", s->cnt);
}
/***********************************************************/

bool is_operator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') return true;
    else return false;
}

short precedence(char c) {
    if (c == '*' || c == '/') return 1;
    else if (c == '+' || c == '-') return 0;
    else return -1;
}

void in2post(Stack *s, char *input, char *output) {
    char *inptr, *outptr;
    char operator;
    bool iw;  // in word
    bool hp;  // higher precedence

    stack_push(s, '(');
    strcat(input, ")");
    inptr = input;
    outptr = output;
    iw = false;
    hp = false;

    while (*inptr) {
        if (*inptr == '(') {
            stack_push(s, *inptr);
        } else if (isdigit(*inptr) || isalpha(*inptr) || *inptr == '.') {
            *outptr++ = *inptr;
            iw = true;
        } else if (is_operator(*inptr)) {
            operator = stack_pop(s);
            hp = false;
            while (is_operator(operator) && precedence(operator) >= precedence(*inptr)) {
                hp = true;
                if (iw) {
                    *outptr++ = ' ';
                    iw = false;
                }
                *outptr++ = operator;
                *outptr++ = ' ';
                operator = stack_pop(s);
            }
            stack_push(s, operator);
            stack_push(s, *inptr);
            if (!hp) {
                *outptr++ = ' ';
            }
        } else if (*inptr == ')') {
            while ((operator = stack_pop(s)) != '(') {
                *outptr++ = ' ';
                *outptr++ = operator;
            }
        } else {
            exit(1);
        }
        ++inptr;
    }
    *outptr = '\0';
}
