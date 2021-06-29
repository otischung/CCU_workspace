// #pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define CHAR 0
#define NUM 1
#define REV 2
#define NUMREV 3

typedef struct NUMER {
    int arr[524288];
    int cnt;
} Numer;

typedef struct WORD {
    char *arr[524288];
    int cnt;
} Word;

void num_init(Numer *n) {
    n->cnt = 0;
}

void word_init(Word *w) {
    w->cnt = 0;
}

int charcmp(const void *_a, const void *_b) {
    char *a = *(char **)_a;
    char *b = *(char **)_b;
    return strcmp(a, b);
}

int charrevcmp(const void *_a, const void *_b) {
    char *a = *(char **)_a;
    char *b = *(char **)_b;
    return strcmp(b, a);
}

int numcmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int numrevcmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}



int main(int argc, char **argv) {
    Word w;
    Numer n;
    short mode;
    char input[1024];
    char *inptr;
    
    if (argc == 1) {
        mode = CHAR;
    } else if (argc == 2 && !strcmp(argv[1], "-n")) {
        mode = NUM;
    } else if (argc == 2 && !strcmp(argv[1], "-r")) {
        mode = REV;
    } else if (argc == 3 && (!strcmp(argv[1], "-n") && !strcmp(argv[2], "-r") || (!strcmp(argv[1], "-r") && !strcmp(argv[2], "-n")))) {
        mode = NUMREV;
    } else {
        fprintf(stderr, "format error\n");
        exit(1);
    }

    word_init(&w);
    num_init(&n);

    while (fgets(input, 1024, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        inptr = input;
        switch (mode) {
        case CHAR:
            w.arr[w.cnt++] = strdup(input);
            break;
        case REV:
            w.arr[w.cnt++] = strdup(input);
            break;
        case NUM:
            while (*inptr) {
                if (!isdigit(*inptr)) {
                    printf("error!!\n");
                    exit(1);
                }
                ++inptr;
            }
            n.arr[n.cnt++] = atoi(input);
            break;
        case NUMREV:
            while (*inptr) {
                if (!isdigit(*inptr)) {
                    printf("error!!\n");
                    exit(1);
                }
                ++inptr;
            }
            n.arr[n.cnt++] = atoi(input);
            break;
        }
    }

    switch (mode) {
    case CHAR:
        qsort(w.arr, w.cnt, sizeof(w.arr[0]), charcmp);
        for (int i = 0; i < w.cnt; ++i) {
            printf("%s\n", w.arr[i]);
        }
        break;
    case REV:
        qsort(w.arr, w.cnt, sizeof(w.arr[0]), charrevcmp);
        for (int i = 0; i < w.cnt; ++i) {
            printf("%s\n", w.arr[i]);
        }
        break;
    case NUM:
        qsort(n.arr, n.cnt, sizeof(n.arr[0]), numcmp);
        for (int i = 0; i < n.cnt; ++i) {
            printf("%d\n", n.arr[i]);
        }
        break;
    case NUMREV:
        qsort(n.arr, n.cnt, sizeof(n.arr[0]), numrevcmp);
        for (int i = 0; i < n.cnt; ++i) {
            printf("%d\n", n.arr[i]);
        }
        break;
    default:
        break;
    }

    return 0;
}
