#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MaxStackLen 64

typedef struct STACK{
    int stack[MaxStackLen];
    short count;
} Stack;

void init(Stack *);
bool isEmpty(Stack *);
bool isFull(Stack *);
void push(Stack *, int);
int pop(Stack *);
void print(Stack *);


/////////////////////////////////////////////////////////////
int main() {
    Stack s;
    init(&s);
    char buf[64];
    int val;

    while (~scanf("%s", buf)) {
        if (!strcmp(buf, "push")) {
            scanf("%d", &val);
            push(&s, val);
        } else if (!strcmp(buf, "pop")) {
            val = pop(&s);
        } else if (!strcmp(buf, "print")) {
            print(&s);
        }
    }

    return 0;
}
/////////////////////////////////////////////////////////////


void init(Stack *s) {
    s->count = 0;
}

bool isEmpty(Stack *s) {
    if (s->count < 1) {
        return true;
    } else {
        return false;
    }
}

bool isFull(Stack *s) {
    if (s->count == MaxStackLen) {
        return true;
    } else {
        return false;
    }
}

void push(Stack *s, int val) {
    if (isFull(s)) {
        printf("Is full!\n");
    } else {
        s->stack[s->count++] = val;
    }
}

int pop(Stack *s) {
    int key;
    if (isEmpty(s)) {
        printf("Is empty!\n");
        return -2147483648;
    } else {
        key = s->stack[--(s->count)];
        printf("Pop %d\n", key);
        return key;
    }
}

void print(Stack *s) {
    printf("Stack:");
    for (int i = 0; i < s->count; ++i) {
        printf(" %d", s->stack[i]);
    }
    putchar('\n');
}