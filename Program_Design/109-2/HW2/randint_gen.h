#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include <fcntl.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

static void randint_gen(int size) {
    FILE *fp;
    bool *repeat;
    int random;
    struct timespec start, end;
    time_t diff;

    if (size > RAND_MAX) {
        fprintf(stderr, "Given size is too large.\n");
        return;
    }
    srand(time(NULL));
    repeat = (bool *)calloc(RAND_MAX, sizeof(bool));
    if (repeat == NULL) {
        perror("malloc failed");
        exit(1);
    }
    fp = fopen("./randint.txt", "w");
    if (fp == NULL) {
        perror("open file error");
        exit(1);
    }
    setvbuf(fp, NULL, _IOFBF, 1048576);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < size; ++i) {
        random = rand();
        if (repeat[random]) {
            --i;
        } else {
            fprintf(fp, "%d\n", random);
            repeat[random] = true;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for random integer generator: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);

    fclose(fp);
    free(repeat);
}
