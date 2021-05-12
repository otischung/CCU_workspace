/*******************************************************************
 * bugs: If enter "1   -1   -   \n", then printf() doesn't work.
 *******************************************************************/
#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxStackLen 8192
#define MaxInputLen 8192

typedef struct STACK {
    double stack[MaxStackLen];
    int size;
} Stack;

void init(Stack *);
void push(Stack *, double);
double pop(Stack *);
void status(Stack *);
void calculate(Stack *, char);


////////////////////////////////////////////////////////
int main() {
    Stack s;
    char input[MaxInputLen];
    // char numbuf[MaxInputLen];
    // char *inputptr;
    // char *numptr;
    char op;
    double num;

    init(&s);
    while (~scanf("%s[^\n]", input)) {
        if (strlen(input) == 1 && strstr("+-*/", input)) {
            op = input[0];
            calculate(&s, op);
        } else {
            sscanf(input, "%lf", &num);
            push(&s, num);
        }

        op = getchar();
        // printf("%d\n", op);
        if (op == '\n') {
            num = pop(&s);
            printf("%.2lf\n", num);
        }
    }

    return 0;
}
////////////////////////////////////////////////////////


void init(Stack *s) {
    s->size = 0;
}

void push(Stack *s, double key) {
    s->stack[s->size++] = key;
}

double pop(Stack *s) {
    return s->stack[--(s->size)];
}

void status(Stack *s) {
    for (int i = 0; i < s->size; ++i) {
        printf("%.2lf ", s->stack[i]);
    }
    printf("\n%d elements\n", s->size);
}

void calculate(Stack *s, char op) {
    double num1, num2, ans;

    num2 = pop(s);
    num1 = pop(s);
    switch (op) {
        case '+':
            ans = num1 + num2;
            break;
        case '-':
            ans = num1 - num2;
            break;
        case '*':
            ans = num1 * num2;
            break;
        case '/':
            ans = num1 / num2;  // div by zero?
            break;
        default:
            ans = 0;
            break;
    }

    push(s, ans);
}
