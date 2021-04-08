#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MaxKeyLen 4096
#define MaxLineLen 4096

typedef struct LNODE {
    char *key;
    struct LNODE *next;
} Lnode;

Lnode *L_insert(Lnode *, char *);  // insert at front.
Lnode *L_delete(Lnode *, char *);


////////////////////////////////////////////////////////////
int main() {
    Lnode *L = NULL;
    return 0;
}
////////////////////////////////////////////////////////////


Lnode *L_insert(Lnode *L, char *key) {
    Lnode *p;

    p = (Lnode *)malloc(sizeof(Lnode));
    p->key = strdup(key);  // You malloc a space.
    if (L) {
        p->next = L->next;
    } else {
        p->next = NULL;
    }

    return p;
}

Lnode *L_delete(Lnode *L, char *key) {
    Lnode *p, *last;

    p = L;
    last = p;

    while (p) {
        if (!strcmp(p->key, key)) {
            if (p == L) {
                last = p->next;
                free(p->key);
                free(p);
                return last;
            }
            last->next = p->next;
            free(p->key);
            free(p);
            return L;
        } else {
            last = p;
            p = p->next;
        }
    }
    return L;
}