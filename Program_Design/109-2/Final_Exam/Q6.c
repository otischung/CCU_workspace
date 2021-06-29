#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct NODE {
    char *key;
    struct NODE *next;
} Node;

Node *insert(Node *n, char *key) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->next = n;
    new->key = strdup(key);
    return new;
}

void print(Node *n) {
    Node *ptr = n;
    while (ptr) {
        printf("%s\n", ptr->key);
        ptr = ptr->next;
    }
}

int main(int argc, char **argv) {
    Node *n = NULL;
    char input[256];
    while (fgets(input, 256, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        n = insert(n, input);
    }
    print(n);
    return 0;
}
