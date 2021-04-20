#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
// #define ARRSIZE 1024  // 2 ^ 10
#define ARRSIZE 16777216  // 2 ^ 24


int main(int argc, char **argv) {
    srand(time(NULL));
    FILE *fp;
    int *arr;
    struct timeval start, end;
    time_t diff;
    int i, j;

    gettimeofday(&start, NULL);
    arr = (int *)malloc(ARRSIZE * sizeof(int));
    if (arr == NULL) {
        perror("Malloc failed");
        return 1;
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Malloc time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    gettimeofday(&start, NULL);
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = rand();
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Generate random string time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    gettimeofday(&start, NULL);
    fp = fopen("./random_int.txt", "w+");
    for (i = 0; i < ARRSIZE; ++i) {
        fprintf(fp, "%d\n", arr[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Write to file time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    fclose(fp);
    return 0;
}
