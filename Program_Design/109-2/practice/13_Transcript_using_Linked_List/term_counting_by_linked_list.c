#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MaxWordLen 1024
#define HWCnt 5

typedef struct NODE {
    char *name;
    int *score;
    int sum;
    struct NODE *next;
    struct NODE *pre;
} Node;

Node *insert(Node *, char *, int *);   // return head
Node *find(Node *, int);     // return the location of key, or NULL if not find.
Node *seek_tail(Node *);        // return the tail of the list, or NULL if list is NULL.
void print(Node *);
void print_reverse(Node *);


/////////////////////////////////////////////////////////
int main() {
    setvbuf(stdout, NULL, _IOFBF, 4096);
    Node *list = NULL;
    char name[MaxWordLen];
    int score[HWCnt];

    while ( ~scanf("%s %d %d %d %d %d", name,\
            &score[0], &score[1], &score[2], &score[3], &score[4]) ) {
        list = insert(list, name, score);
    }

    print(list);

    return 0;
}
/////////////////////////////////////////////////////////


Node *insert(Node *head, char *key, int *score) {
    Node *newNode;
    Node *traverseptr;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->sum = 0;
    newNode->name = strdup(key);
    newNode->score = calloc(HWCnt, sizeof(int));
    for (int i = 0; i < HWCnt; ++i) {
        newNode->score[i] = score[i];
        newNode->sum += score[i];
    }
    newNode->next = NULL;
    newNode->pre = NULL;

    if (head == NULL) {
        return newNode;
    }

    traverseptr = find(head, newNode->sum);
    if (traverseptr == head) {  // insert at head
        traverseptr->pre = newNode;
        newNode->next = traverseptr;
        newNode->pre = NULL;
        return newNode;
    } else if (traverseptr != head && traverseptr) {
        traverseptr->pre->next = newNode;
        newNode->pre = traverseptr->pre;
        newNode->next = traverseptr;
        traverseptr->pre = newNode;
        return head;
    } else {  // insert at tail
        traverseptr = seek_tail(head);
        traverseptr->next = newNode;
        newNode->next = NULL;
        newNode->pre = traverseptr;
        return head;
    }
}

Node *find(Node *head, int sum) {
    Node *traverse = head;
    while (traverse) {
        if (traverse->sum < sum) {
            return traverse;
        }
        traverse = traverse->next;
    }
    return NULL;
}

Node *seek_tail(Node *head) {
    Node *traverse;

    if (head == NULL) {
        return NULL;
    }
    traverse = head;
    while (traverse->next) {
        traverse = traverse->next;
    }
    return traverse;
}

void print(Node *head) {
    Node *traverse;
    int i;

    if (head == NULL) {
        printf("NULL\n");
    }
    traverse = head;
    while (traverse) {
        printf("%s\t", traverse->name);
        for (i = 0; i < HWCnt - 1; ++i) {
            printf("%d\t", traverse->score[i]);
        }
        printf("%d\n", traverse->score[i]);
        traverse = traverse->next;
    }
}

void print_reverse(Node *head) {
    Node *tail;
    int i;

    if (head == NULL) {
        printf("NULL\n");
    }
    tail = seek_tail(head);
    while (tail) {
        printf("%s\t", tail->name);
        for (i = 0; i < HWCnt - 1; ++i) {
            printf("%d\t", tail->score[i]);
        }
        printf("%d\n", tail->score[i]);
        tail = tail->pre;
    }
}