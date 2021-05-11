#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXHASH (1 << 20)
#define int32 unsigned int

typedef struct DNODE {
    char *key;
    int cnt;
    struct DNODE *next;
} DNode;

// void hash_init(DNode **hTab, int maxHash) {
//     hTab = (DNode **)calloc(maxHash, sizeof(DNode *));
    
// }

int32 hash65(char *key);
void hash_insert(DNode **hTab, int maxHash, char *key);
DNode *hash_find(DNode **hTab, int maxHash, char *key);
DNode *l_insert(DNode *L, char *key);
DNode *l_find(DNode *L, char *key);
void traverse(DNode *L);


//////////////////////////////////////////////////////////////////////////////////////
int main() {
    DNode **hTab, *dptr;
    char line[4096];
    const int MaxLine = 1024;
    
    hTab = (DNode **)calloc(MAXHASH, sizeof(DNode *));
    
    while (fgets(line, MaxLine, stdin) != NULL) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] =  '\0';
        }

        dptr = hash_find(hTab, MAXHASH, line);
        if (dptr) {
            ++(dptr->cnt);
        } else {
            hash_insert(hTab, MAXHASH, line);
        }
    }

    for (int i = 0; i < MAXHASH; ++i) {
        if (hTab[i] != NULL) traverse(hTab[i]);
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////


int32 hash65(char *key) {
    int32 hv = 1;
    char *ptr = key;

    while (*ptr) {
        hv = hv << 6 + hv + *ptr++;  // hv * 65 + *ptr
    }
    return hv;
}

void hash_insert(DNode **hTab, int maxHash, char *key) {
    DNode *L;
    int32 hv = hash65(key) % maxHash;
    L = hTab[hv];
    hTab[hv] = l_insert(L, key);
}

DNode *hash_find(DNode **hTab, int maxHash, char *key) {
    int32 hv = hash65(key) % maxHash;
    DNode *dptr = hTab[hv];
    return l_find(dptr, key);
}

DNode *l_insert(DNode *L, char *key) {
    DNode *p = (DNode *)malloc(sizeof(DNode));
    p->key = strdup(key);
    p->cnt = 1;
    p->next = L;
    return p;
}

DNode *l_find(DNode *L, char *key) {
    DNode *p = L;
    if (L == NULL) return NULL;

    while (p) {
        if (!strcmp(p->key, key)) return p;
        p = p->next;
    }
    return NULL;
}

void traverse(DNode *L) {
    // ...
    return;
}
