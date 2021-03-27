#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxCnt (1 << 30)
#define SMALLER 0
#define LARGER 1
#define TYPE int

typedef struct STACK {
    int memberCnt;
    int arrSize;
    TYPE *arr;
    int top;
} Stack;

bool stack_init(Stack *s) {
    s->memberCnt = 0;
    s->arrSize = 1;
    s->arr = calloc(s->arrSize, sizeof(TYPE));
    if (s->arr == NULL) {
        fprintf(stderr, "malloc failed\n");
        return false;
    }
    s->top = 0;
    return true;
}

bool stack_realloc(Stack *s, bool mode) {
    if (mode == LARGER) {
        s->arrSize <<= 1;
        s->arr = realloc(s->arr, s->arrSize * sizeof(TYPE));
        if (s->arr == NULL) {
            fprintf(stderr, "realloc failed\n");
            return false;
        }
    } else {
        s->arrSize >>= 1;
        s->arr = realloc(s->arr, s->arrSize * sizeof(TYPE));
    }
    return true;
}

void stack_status(Stack *s) {
    printf("memberCnt = %d\n", s->memberCnt);
    printf("arrsize = %d\n", s->arrSize);
    for (int i = 0; i < s->memberCnt; ++i) {
        printf("%d ", s->arr[i]);
    }
    putchar('\n');
}

bool stack_push(Stack *s, TYPE data) {
    bool success = true;
    if (s->memberCnt == s->arrSize) {
        success = stack_realloc(s, LARGER);
        stack_push(s, data);
    } else {
        s->arr[s->memberCnt++] = data;
    }
    return success;
}

TYPE stack_pop(Stack *s) {
    TYPE result;
    bool success = true;

    if (s->memberCnt < 1) {
        fprintf(stderr, "No element.\n");
        return 0;
    }
    result = s->arr[s->memberCnt - 1];
    s->memberCnt -= 1;
    if (s->memberCnt == s->arrSize >> 1) {
        success = stack_realloc(s, SMALLER);
    }
    return result;
}

int main() {
    Stack s;
    stack_init(&s);
    stack_status(&s);
    stack_push(&s, 1);
    stack_status(&s);
    stack_push(&s, 2);
    stack_status(&s);
    stack_push(&s, 3);
    stack_status(&s);
    stack_push(&s, 4);
    stack_status(&s);
    stack_push(&s, 5);
    stack_status(&s);

    stack_pop(&s);
    stack_status(&s);
    stack_pop(&s);
    stack_status(&s);
    stack_pop(&s);
    stack_status(&s);
    stack_pop(&s);
    stack_status(&s);
    stack_pop(&s);
    stack_status(&s);
    stack_pop(&s);
    stack_status(&s);

    return 0;
}