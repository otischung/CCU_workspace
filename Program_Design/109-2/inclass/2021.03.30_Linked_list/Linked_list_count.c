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

typedef struct LCNTNODE {
    char *key;
    int cnt;
    struct LCNTNODE *next;
} LCntNode;

LCntNode *LInsert_front(LCntNode *L, char *key);
LCntNode *LInsert_tail(LCntNode *L, char *key);
LCntNode *LFind(LCntNode *L, char *key);
void LPrint(LCntNode *L);

///////////////////////////////////////////////////////////////////////////
int main() {
    // LCntNode *keyList = NULL;
    LCntNode *keyList = NULL;
    LCntNode *ptr;
    char line[MaxLineLen];
    while (fgets(line, MaxLineLen, stdin) != NULL) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if ((ptr = LFind(keyList, line)) == NULL)
            keyList = LInsert_tail(keyList, line);
        else
            ++(ptr->cnt);
    }
    LPrint(keyList);
    return 0;
}
///////////////////////////////////////////////////////////////////////////

LCntNode *LInsert_front(LCntNode *L, char *key) {
    LCntNode *ptr;
    ptr = (LCntNode *)malloc(sizeof(LCntNode *));  // you malloc a space here.
    ptr->key = strdup(key);  // you malloc a space here.
    ptr->cnt = 1;
    ptr->next = L;
    // L = ptr;
    return ptr;
}

LCntNode *LInsert_tail(LCntNode *L, char *key) {
    LCntNode *ptr, *ptr_origin;
    ptr = (LCntNode *)malloc(sizeof(LCntNode *));  // you malloc a space here.
    ptr->key = strdup(key);  // you malloc a space here.
    ptr->cnt = 1;
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

LCntNode *LFind(LCntNode *L, char *key) {
    LCntNode *ptr = L;

    while (ptr) {
        if (!strcmp(ptr->key, key)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void LPrint(LCntNode *L) {
    LCntNode *ptr = L;
    
    while (ptr) {
        printf("%d\t%s\n", ptr->cnt, ptr->key);
        ptr = ptr->next;
    }
    // printf("NULL\n");
}