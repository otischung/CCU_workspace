#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MaxQueueLen 64

typedef struct QUEUE{
    int queue[MaxQueueLen];
    short front;
    short end;
} Queue;

void init(Queue *);
bool isEmpty(Queue *);
bool isFull(Queue *);
void push(Queue *, int);
int pop(Queue *);
void print(Queue *);


/////////////////////////////////////////////////////////////
int main() {
    Queue q;
    init(&q);
    char buf[64];
    int val;

    while (~scanf("%s", buf)) {
        if (!strcmp(buf, "push")) {
            scanf("%d", &val);
            push(&q, val);
        } else if (!strcmp(buf, "pop")) {
            val = pop(&q);
        } else if (!strcmp(buf, "print")) {
            print(&q);
        }
    }

    return 0;
}
/////////////////////////////////////////////////////////////


void init(Queue *q) {
    q->front = 0;
    q->end = 0;
}

bool isEmpty(Queue *q) {
    if (q->front == q->end) {
        return true;
    } else {
        return false;
    }
}

bool isFull(Queue *q) {
    if (q->front == q->end - 1 || (q->end == 0 && q->front == MaxQueueLen - 1)) {
        return true;
    } else {
        return false;
    }
}

void push(Queue *q, int val) {
    if (isFull(q)) {
        printf("Is full!\n");
    } else {
        q->queue[q->front] = val;
        q->front = (q->front + 1) % MaxQueueLen;
    }
}

int pop(Queue *q) {
    int key;
    if (isEmpty(q)) {
        printf("Is empty!\n");
        return -2147483648;
    } else {
        key = q->queue[q->end];
        q->end = (q->end + 1) % MaxQueueLen;
        printf("Pop %d\n", key);
        return key;
    }
}

void print(Queue *q) {
    printf("Queue:");
    short idx = q->end;
    while (idx != q->front) {
        printf(" %d", q->queue[idx]);
        idx = (idx + 1) % MaxQueueLen;
    }
    putchar('\n');
}