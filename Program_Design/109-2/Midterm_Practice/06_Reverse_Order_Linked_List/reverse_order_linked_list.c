#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char *key;
    struct NODE *next;
} Node;

Node *insert(Node *head, char *key);
Node *find(Node *head, char *key);
void llprint(Node *head);

int main() {
    Node *head = NULL;
    char input[1024];

    while (fgets(input, 1024, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        if (find(head, input) == NULL) {
            head = insert(head, input);
        }
    }
    
    llprint(head);
    return 0;
}

Node *insert(Node *head, char *key) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->next = head;
    return newNode;
}

Node *find(Node *head, char *key) {
    Node *traverse = head;
    if (traverse == NULL) return NULL;
    while (traverse) {
        if (!strcmp(traverse->key, key)) return traverse;
        traverse = traverse->next;
    }
    return NULL;
}

void llprint(Node *head) {
    Node *traverse = head;
    if (traverse == NULL) return;
    while (traverse) {
        printf("%s\n", traverse->key);
        traverse = traverse->next;
    }
}
