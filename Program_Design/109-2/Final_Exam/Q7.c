#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct NODE {
    char *key;
    struct NODE *left;
    struct NODE *right;
} Node;

Node *insert(Node *n, char *key) {
    Node *new, *traverse;
    if (n == NULL) {
        new = (Node *)malloc(sizeof(Node));
        new->key = strdup(key);
        new->left = NULL;
        new->right = NULL;
        return new;
    }

    traverse = n;
    if (strcmp(key, traverse->key) <= 0) {
        traverse->left = insert(traverse->left, key);
    } else {
        traverse->right = insert(traverse->right, key);
    }
    return n;
}

void inorder(Node *n) {
    if (n->left != NULL) inorder(n->left);
    printf("%s\n", n->key);
    if (n->right != NULL) inorder(n->right);
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
    inorder(n);
    return 0;
}
