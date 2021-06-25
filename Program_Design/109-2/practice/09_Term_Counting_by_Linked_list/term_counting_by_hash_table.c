#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#define HASHSIZE 8192

typedef struct NODE {
    char *key;
    int cnt;
    struct NODE *next;
} Node;

typedef struct HASH {
    Node *arr[HASHSIZE];
    int cnt;
} Hash;

void node_init(Node *n);
void hash_init(Hash *h);
uint8_t hash_function(Hash *h, char *key);
void hash_insert(Hash *h, char *key);
void hash_print(Hash *h);
void hash_free(Hash *h);


/////////////////////////////////////////////////////////////////////
int main() {
    Hash h;
    char input[1024];

    hash_init(&h);

    while (fgets(input, 1024, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        hash_insert(&h, input);
    }
    hash_print(&h);
    hash_free(&h);
    return 0;
}
/////////////////////////////////////////////////////////////////////


void node_init(Node *n) {
    n->cnt = 0;
}

void hash_init(Hash *h) {
    h->cnt = 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        h->arr[i] = NULL;
    }
}

uint8_t hash_function(Hash *h, char *key) {
    uint64_t hv;  // hash value
    char *ptr;

    hv = 0;
    ptr = key;
    while (*ptr) {
        hv = hv * 31 + *ptr++;
        hv %= HASHSIZE;
    }

    return (uint8_t)hv;
}

void hash_insert(Hash *h, char *key) {
    uint8_t hv;
    Node *new, *traverse, *pre;
    char *keyptr;
    bool delete = false;
    static const Node newnode = {
        .cnt = 1,
        .key = NULL,
        .next = NULL,
    };

    keyptr = key;
    if (keyptr[0] == '-') {
        delete = true;
        ++keyptr;
    }
    hv = hash_function(h, keyptr);
    if (h->arr[hv] == NULL) {
        new = (Node *)malloc(sizeof(Node));
        *new = newnode;
        new->key = strdup(keyptr);
        h->arr[hv] = new;
        ++h->cnt;
    } else {
        traverse = h->arr[hv];
        pre = traverse;
        while (traverse) {
            if (!strcmp(traverse->key, keyptr)) {
                if (delete) {
                    --traverse->cnt;
                    return;
                } else {
                    ++traverse->cnt;
                    return;
                }
            }
            pre = traverse;
            traverse = traverse->next;
        }
        new = (Node *)malloc(sizeof(Node));
        *new = newnode;
        new->key = strdup(keyptr);
        pre->next = new;
        ++h->cnt;
    }
}

void hash_print(Hash *h) {
    Node *traverse;
    for (int i = 0; i < HASHSIZE; ++i) {
        if (h->arr[i] != NULL) {
            traverse = h->arr[i];
            while (traverse) {
                printf("%s: %d\n", traverse->key, traverse->cnt);
                traverse = traverse->next;
            }
        }
    }
}

void hash_free(Hash *h) {
    Node *traverse, *pre;
    for (int i = 0; i < HASHSIZE; ++i) {
        if (h->arr[i] != NULL) {
            traverse = h->arr[i];
            while (traverse) {
                free(traverse->key);
                pre = traverse;
                traverse = traverse->next;
                free(pre);
            }
        }
    }
}
