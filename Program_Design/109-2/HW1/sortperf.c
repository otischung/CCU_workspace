#include "sort_int.h"
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
    int *arr;
    int tmp;
    int i;
    struct timeval start, end;
    time_t diff;
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
    printf("%s used %.2Lf seconds.\n", method, (long double)diff / 1000000);
    // for (int i = 0; i < ARRSIZE; ++i) {
    //     printf("%d\n", arr[i]);
    // }
    
    fclose(fp);
    free(arr);
    return 0;
}
