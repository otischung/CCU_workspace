#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct WORD {
    char *key;
    int cnt;
} Word;

Word *find(Word *arr, int wordCnt, char *key);
int cmp(const void *_a, const void *_b);

int main() {
    Word *arr = (Word *)calloc((1 << 15), sizeof(Word));
    Word *ptr;
    int wordCnt = 0;
    char input[1024];

    while (~scanf("%s", input)) {
        if (input[0] == 'a' || input[0] == 'A') {
            ptr = find(arr, wordCnt, input);
            if (ptr) ++(ptr->cnt);
            else {
                arr[wordCnt].key = strdup(input);
                arr[wordCnt].cnt = 1;
                ++wordCnt;
            }
        }
    }

    qsort(arr, wordCnt, sizeof(arr[0]), cmp);

    for (int i = 0; i < wordCnt; ++i) {
        printf("%s\t%d\n", arr[i].key, arr[i].cnt);
    }

    return 0;
}

Word *find(Word *arr, int wordCnt, char *key) {
    for (int i = 0; i < wordCnt; ++i) {
        if (!strcmp(arr[i].key, key)) return &arr[i];
    }
    return NULL;
}

int cmp(const void *_a, const void *_b) {
    Word *a = (Word *)_a;
    Word *b = (Word *)_b;

    if (a->cnt < b->cnt) return 1;
    else if (a->cnt > b->cnt) return -1;
    else return strcmp(a->key, b->key);
}
