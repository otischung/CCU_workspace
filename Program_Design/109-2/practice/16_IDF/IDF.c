#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define HASHSIZE 2097152  // 2^21

typedef struct DIC {
    char *key;
    int cnt;
    int insertLine;
    struct DIC *next;
} Dic;

typedef struct DICARR {
    Dic **arr;
    int size;
    int cnt;
} DicArr;

Dic *DicHash[HASHSIZE];

uint32_t hash(char *str);
void dic_init(DicArr *da);
void dic_realloc(DicArr *da);
void dic_free(DicArr *da);
Dic *dic_insert(Dic *d, char *key, int line);
void insert(char *key, int line);
void dic_hash2arr(DicArr *da);
int cmp(const void *_a, const void *_b);


///////////////////////////////////////////////////////////////
int main() {
    char input[131072];  // 2^17
    char delm[] = " \n\r\t";
    char *inputptr, *inputsaveptr;
    DicArr dic;
    int getline = 0;

    setvbuf(stdout, NULL, _IOFBF, 8192);
    dic_init(&dic);
    memset(DicHash, 0, sizeof(Dic *) * HASHSIZE);
    while (fgets(input, 131072, stdin) != NULL) {
        inputptr = input;

        inputptr = strtok_r(inputptr, delm, &inputsaveptr);
        while (inputptr) {
            insert(inputptr, getline);
            inputptr = strtok_r(NULL, delm, &inputsaveptr);
        }
        ++getline;
    }

    dic_hash2arr(&dic);

    // for (int i = 0; i < dic.cnt; ++i) {
    //     printf("%s%c", dic.arr[i]->key, " \n"[i == dic.cnt - 1]);
    // }
    // for (int i = 0; i < dic.cnt; ++i) {
    //     printf("%d%c", dic.arr[i]->cnt, " \n"[i == dic.cnt - 1]);
    // }

    qsort(dic.arr, dic.cnt, sizeof(dic.arr[0]), cmp);

    // for (int i = 0; i < dic.cnt; ++i) {
    //     printf("%s%c", dic.arr[i]->key, " \n"[i == dic.cnt - 1]);
    // }
    // for (int i = 0; i < dic.cnt; ++i) {
    //     printf("%d%c", dic.arr[i]->cnt, " \n"[i == dic.cnt - 1]);
    // }

    for (int i = 0; i < dic.cnt; ++i) {
        printf("%s\n", dic.arr[i]->key);
        if (i == 9) break;
    }

    dic_free(&dic);
    return 0;
}
///////////////////////////////////////////////////////////////


uint32_t hash(char *str) {
    int l = strlen(str);
    uint32_t ret = 0;
    for (int i = 0; i < l; i++) {
        ret *= 31;
        ret += (uint8_t) str[i] % 31;
    }
    return ret;
}

void dic_init(DicArr *da) {
    da->arr = calloc(1024, sizeof(Dic *));
    da->size = 1024;
    da->cnt = 0;
}

void dic_realloc(DicArr *da) {
    da->size <<= 1;
    da->arr = realloc(da->arr, da->size * sizeof(Dic *));
}

void dic_free(DicArr *da) {
    for (int i = 0; i < da->cnt; ++i)
        free(da->arr[i]->key);
    free(da->arr);
    da->cnt = 0;
    da->size = 0;
}

Dic *dic_insert(Dic *d, char *key, int line) {
    static const Dic init_dic = {
        .insertLine = -1,
        .next = NULL,
        .key = NULL,
        .cnt = 1,
    };

    if (d == NULL) {
        d = malloc(sizeof(Dic));
        *d = init_dic;
        d->key = strdup(key);
        d->insertLine = line;
        return d;
    }

    if (!strcmp(d->key, key)) {
        if (d->insertLine != line) {
            ++(d->cnt);
            d->insertLine = line;
        }
        return d;
    }
    d->next = dic_insert(d->next, key, line);
    return d;
}

void insert(char *key, int line) {
    uint32_t hv = hash(key) % HASHSIZE;
    DicHash[hv] = dic_insert(DicHash[hv], key, line);
}

void dic_hash2arr(DicArr *da) {
    Dic *ptr;

    for (int i = 0; i < HASHSIZE; ++i) {
        ptr = DicHash[i];
        while (ptr != NULL) {
            da->arr[da->cnt++] = ptr;
            if (da->cnt == da->size) {
                dic_realloc(da);
            }
            ptr = ptr->next;
        }
    }
}

int cmp(const void *_a, const void *_b) {
    Dic *a = *(Dic **)_a;
    Dic *b = *(Dic **)_b;

    if (a->cnt < b->cnt) return 1;
    else if (a->cnt == b->cnt) {
        // if (a->key[0] < 0 && b->key[0] > 0) return 1;
        // if (a->key[0] > 0 && b->key[0] < 0) return 0;
        // if (a->key[0] > 0 && b->key[0] > 0) {
        //     if (strcmp(a->key, b->key) > 0) return 1;
        //     else return 0;
        // }
        // if (a->key[0] < 0 && b->key[0] < 0) {
        //     if (strcmp(a->key, b->key) > 0) return 1;
        //     else return 0;
        // }
        return strcmp(a->key, b->key);
    }
    else return 0;
}

/* stdin
a b b b b c D
a a d C
GAIS 輸入法 牛 b
要 不能 畢業 了 a a a ， 人生 阿
I eat apple .
十個 字 十個 字
人生 好難
出題 好 麻煩 .
記得 戴 口罩
*/


/* stdout
a
.
b
人生
C
D
GAIS
I
apple
c
*/
