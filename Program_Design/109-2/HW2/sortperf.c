#include "sort_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <libgen.h>

int main(int argc, char **argv) {
    // setvbuf(stdout, NULL, _IOFBF, ARRSIZE);
    srand(time(NULL));
    char *method;
    int *arr;
    int tmp;
    int i;
    clock_t start, end;
    FILE *fp;

    method = basename(argv[0]);
    arr = (int *)malloc(ARRSIZE * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }

    i = 0;
    fp = fopen("./random_int.txt", "r");
    while (~fscanf(fp, "%d", &tmp)) {
        arr[i++] = tmp;
    }

    start = clock();
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
    end = clock();

    printf("%s used %ld microseconds.\n", method, end - start);
    printf("%s used %.2Lf seconds.\n", method, ((long double)(end - start)/1000000));
    // for (int i = 0; i < ARRSIZE; ++i) {
    //     printf("%d\n", arr[i]);
    // }

    free(arr);
    return 0;
}
