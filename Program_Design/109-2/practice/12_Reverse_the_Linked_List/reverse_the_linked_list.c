#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MaxWordLen 1024

typedef struct NODE {
    char *name;
    int count;
    struct NODE *next;
    struct NODE *pre;
} Node;

Node *insert(Node *, char *);   // return head
Node *find(Node *, char *);     // return the location of key, or NULL if not find.
Node *seek_tail(Node *);        // return the tail of the list, or NULL if list is NULL.
void print(Node *);
void print_reverse(Node *);


/////////////////////////////////////////////////////////
int main() {
    setvbuf(stdout, NULL, _IOFBF, 4096);
    Node *list = NULL;
    Node *list_last;
    Node *seek;
    char name[MaxWordLen];

    while (~scanf("%s", name)) {
        if ((seek = find(list, name)) == NULL) {
            list = insert(list, name);
        }
    }
    
    print_reverse(list);
    print(list);

    return 0;
}
/////////////////////////////////////////////////////////


Node *insert(Node *head, char *key) {
    Node *newNode;
    Node *traverseptr;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->name = strdup(key);
    newNode->count = 1;
    newNode->next = NULL;
    newNode->pre = NULL;

    if (head == NULL) {
        return newNode;
    }

    traverseptr = seek_tail(head);
    traverseptr->next = newNode;
    newNode->next = NULL;
    newNode->pre = traverseptr;
    
    return head;
}

Node *find(Node *head, char *key) {
    Node *traverse = head;
    while (traverse) {
        if (!strcmp(traverse->name, key)) {
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

    if (head == NULL) {
        printf("NULL\n");
    }
    traverse = head;
    while (traverse) {
        printf("%s\n", traverse->name);
        traverse = traverse->next;
    }
}

void print_reverse(Node *head) {
    Node *tail;

    if (head == NULL) {
        printf("NULL\n");
    }
    tail = seek_tail(head);
    while (tail) {
        printf("%s\n", tail->name);
        tail = tail->pre;
    }
}
