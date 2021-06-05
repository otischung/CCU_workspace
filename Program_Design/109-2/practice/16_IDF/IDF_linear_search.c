#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LINEDIC 0
#define MAINDIC 1

typedef struct DIC {
    char *key;
    int cnt;
} Dic;

typedef struct DICARR {
    Dic *arr;
    int size;
    int cnt;
} DicArr;

void dic_init(DicArr *da);
void dic_realloc(DicArr *da);
void dic_free(DicArr *da);
void dic_insert(DicArr *da, char *key, bool mode);
int cmp(const void *_a, const void *_b);


///////////////////////////////////////////////////////////////
int main() {
    char input[131072];  // 2^17
    char delm[] = " \n\r\t";
    char *inputptr, *inputsaveptr;
    DicArr dic, line;

    setvbuf(stdout, NULL, _IOFBF, 8192);
    dic_init(&dic);
    while (fgets(input, 131072, stdin) != NULL) {
        dic_init(&line);
        inputptr = input;

        inputptr = strtok_r(inputptr, delm, &inputsaveptr);
        while (inputptr) {
            dic_insert(&line, inputptr, LINEDIC);
            inputptr = strtok_r(NULL, delm, &inputsaveptr);
        }
        for (int i = 0; i < line.cnt; ++i) {
            dic_insert(&dic, line.arr[i].key, MAINDIC);
        }
        // for (int i = 0; i < dic.cnt; ++i) {
        //     printf("%s%c", dic.arr[i].key, " \n"[i == dic.cnt - 1]);
        // }
        // for (int i = 0; i < dic.cnt; ++i) {
        //     printf("%d%c", dic.arr[i].cnt, " \n"[i == dic.cnt - 1]);
        // }
        dic_free(&line);
    }

    qsort(dic.arr, dic.cnt, sizeof(dic.arr[0]), cmp);

    for (int i = 0; i < dic.cnt; ++i) {
        printf("%s%c", dic.arr[i].key, " \n"[i == dic.cnt - 1]);
    }
    for (int i = 0; i < dic.cnt; ++i) {
        printf("%d%c", dic.arr[i].cnt, " \n"[i == dic.cnt - 1]);
    }

    for (int i = 0; i < dic.cnt; ++i) {
        printf("%s\n", dic.arr[i].key);
        if (i == 9) break;
    }

    dic_free(&dic);
    return 0;
}
///////////////////////////////////////////////////////////////

void dic_init(DicArr *da) {
    da->arr = calloc(1024, sizeof(Dic));
    da->size = 1024;
    da->cnt = 0;
}

void dic_realloc(DicArr *da) {
    da->size <<= 1;
    da->arr = realloc(da->arr, da->size * sizeof(Dic));
}

void dic_free(DicArr *da) {
    for (int i = 0; i < da->cnt; ++i)
        free(da->arr[i].key);
    free(da->arr);
    da->cnt = 0;
    da->size = 0;
}

void dic_insert(DicArr *da, char *key, bool mode) {
    for (int i = 0; i < da->cnt; ++i) {
        if (!strcmp(da->arr[i].key, key)) {
            if (mode == LINEDIC)
                return;
            else {
                ++(da->arr[i].cnt);
                return;
            }
        }
    }

    if (da->cnt == da->size)
        dic_realloc(da);
    da->arr[da->cnt].key = strdup(key);
    ++(da->arr[da->cnt].cnt);
    ++(da->cnt);
}

int cmp(const void *_a, const void *_b) {
    Dic *a = (Dic *)_a;
    Dic *b = (Dic *)_b;

    if (a->cnt < b->cnt) return 1;
    else if (a->cnt == b->cnt) {
        if (a->key[0] < 0 && b->key[0] > 0) return 1;
        if (a->key[0] > 0 && b->key[0] < 0) return 0;
        if (a->key[0] > 0 && b->key[0] > 0) {
            if (strcmp(a->key, b->key) > 0) return 1;
            else return 0;
        }
        if (a->key[0] < 0 && b->key[0] < 0) {
            if (strcmp(a->key, b->key) > 0) return 1;
            else return 0;
        }
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
