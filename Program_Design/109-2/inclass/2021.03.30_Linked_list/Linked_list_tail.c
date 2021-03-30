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

Lnode *LInsert_front(Lnode *L, char *key);
Lnode *LInsert_tail(Lnode *L, char *key);
Lnode *LFind(Lnode *L, char *key);
void LPrint(Lnode *L);

///////////////////////////////////////////////////////////////////////////
int main() {
    Lnode *keyList = NULL;
    char line[MaxLineLen];
    while (fgets(line, MaxLineLen, stdin) != NULL) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (LFind(keyList, line) == NULL)
            keyList = LInsert_tail(keyList, line);
    }
    LPrint(keyList);
    return 0;
}
///////////////////////////////////////////////////////////////////////////

Lnode *LInsert_front(Lnode *L, char *key) {
    Lnode *ptr;
    ptr = (Lnode *)malloc(sizeof(Lnode *));  // you malloc a space here.
    ptr->key = strdup(key);  // you malloc a space here.
    ptr->next = L;
    // L = ptr;
    return ptr;
}

Lnode *LInsert_tail(Lnode *L, char *key) {
    Lnode *ptr, *ptr_origin;
    ptr = (Lnode *)malloc(sizeof(Lnode *));  // you malloc a space here.
    ptr->key = strdup(key);  // you malloc a space here.
    ptr_origin = ptr;

    if (L == NULL) {
        ptr->next = NULL;
        return ptr;
    }
    ptr = L;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = ptr_origin;
    ptr_origin->next = NULL;
    
    return L;  // return head.
}

Lnode *LFind(Lnode *L, char *key) {
    Lnode *ptr = L;

    while (ptr) {
        if (!strcmp(ptr->key, key)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void LPrint(Lnode *L) {
    Lnode *ptr = L;
    
    while (ptr) {
        printf("%s -> ", ptr->key);
        ptr = ptr->next;
    }
    printf("NULL\n");
}