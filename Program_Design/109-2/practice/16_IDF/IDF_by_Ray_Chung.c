#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define N 2000000 // 2M
typedef struct Node {
    int lastIns;
    struct Node *next;
    char *val;
    int cnt;
} Node;
Node *table[N];
static inline int min(int a, int b) {
    if (a > b) return b;
    return a;
}
uint32_t hash(char *str) {
    int l = strlen(str);
    uint32_t ret = 0;
    for (int i = 0; i < l; i++) {
        ret *= 31;
        ret += (uint8_t) str[i] % 31;
    }
    return ret;
}
 
Node *insert_list(Node *ptr, char *s, int line) {
    static const Node blank_node = {
        .lastIns = -1,
        .next = NULL,
        .val = NULL,
        .cnt = 0,
    };
    if (ptr == NULL) {
        ptr = malloc(sizeof(Node));
        *ptr = blank_node;
        ptr->val = strdup(s);
        ptr->cnt = 1;
        ptr->lastIns = line;
        return ptr;
    }
    if (!strcmp(ptr->val, s)) {
        if (ptr->lastIns!= line) {ptr->cnt++; ptr->lastIns = line;}
        return ptr;
    }
    ptr->next = insert_list(ptr->next, s, line);
    return ptr;
}
 
void insert(char *s, int line) {
    table[hash(s) % N] = insert_list(table[hash(s) % N], s, line);
}
 
Node *result[8192000];
int cmp(const void *_a, const void *_b) {
    Node *a = *(Node**)_a;
    Node *b = *(Node**)_b;
    if (a->cnt == b->cnt) return strcmp(a->val, b->val) > 0;
    return a->cnt < b->cnt;
    
}
char buf[8192000];
int main() {
    for (int i = 1; fgets(buf, 819200, stdin); i++) {
        for (char *saveptr, *word = strtok_r(buf, " \t\n", &saveptr);
            word;
            word = strtok_r(NULL, " \t\n", &saveptr)) {
            insert(word, i);
        }
    }
    
    int n = 0;
    for (int i = 0; i < N; i++) {
        Node *ptr = table[i];
        while (ptr != NULL) {
            result[n++] = ptr;
            ptr = ptr->next;
        }
    }
    qsort(result, n, sizeof(result[0]), cmp);
    for (int i = 0; i < min(10, n); i++) {
        printf("%s\n", result[i]->val);
    }
}
