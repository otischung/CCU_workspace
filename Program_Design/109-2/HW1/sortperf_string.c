#include "sort_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    // setvbuf(stdout, NULL, _IOFBF, ARRSIZE);
    srand(time(NULL));
    char *method;
    char **arr;
    char buf[128];
    struct timeval start, end;
    time_t diff;
    short mode; // 0: number, 1: A-Z, 2: a-z
    FILE *fp;
    int i;

    method = basename(argv[0]);
    arr = (char **)malloc(ARRSIZE * sizeof(char *));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = (char *)malloc(128 * sizeof(char));
        if (arr[i] == NULL) {
            perror("malloc failed");
            return 1;
        }
    }

    fp = fopen("./random_string.txt", "r");
    if (fp == NULL) {
        perror("Open file error");
        return 1;
    }

    i = 0;
    while (fgets(buf, 128, fp) != NULL) {
        if (i == ARRSIZE) break;
        strcpy(arr[i++], buf);
    }

    gettimeofday(&start, NULL);
    if (!strcmp(method, "mergesort")) {
        mergesort(arr, ARRSIZE);
    } else if (!strcmp(method, "heapsort")) {
        heapsort(arr, ARRSIZE);
    } else if (!strcmp(method, "quicksort")) {
        quicksort(arr, ARRSIZE);
    } else {
        method = "qsort";
        qsort(arr, ARRSIZE, sizeof(arr[0]), cmp);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("%s used %ld microseconds.\n", method, diff);
    printf("%s used %.2lf microseconds.\n", method, (double)diff / 1000000.0);

    // for (int i = 0; i < ARRSIZE; ++i) {
    //     printf("%s", arr[i]);
    // }
    // putchar('\n');

    for (int i = 0; i < ARRSIZE; ++i) {
        free(arr[i]);
    }
    
    fclose(fp);
    free(arr);
    return 0;
}
