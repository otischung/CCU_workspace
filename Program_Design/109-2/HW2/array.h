#pragma once
#include "randint_gen.h"

void array_linear_search(int arrsize, int query);
void linear_search(int *arr, int arrsize, int key);

void array_linear_search(int arrsize, int query) {
    FILE *fp;
    int *arr;
    int num;
    struct timespec start, end;
    time_t diff;
    // int numcnt = 0;
    // long cpu_threads;
    // cpu_set_t mask;
    // pthread_t *task;

    // if (access("./randint.txt", F_OK) != 0 || force) {
        // randint_gen(arrsize);
    // }

    fp = fopen("./randint.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }

    // cpu_threads = sysconf(_SC_NPROCESSORS_CONF);
    // task = (pthread_t *)calloc(cpu_threads, sizeof(pthread_t));

    arr = (int *)calloc(arrsize, sizeof(int));
    for (int i = 0; i < arrsize; ++i) {
        // pthread_create(&task[0], NULL, file2array, (void *)data);
        fscanf(fp, "%d", &num);
        // ++numcnt;
        // if (numcnt <= arrsize) {
            arr[i] = num;
        // } else {
        //     array_linear_search(arrsize, query, true);
        // }
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < query; ++i) {
        linear_search(arr, arrsize, rand());
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for linear search to array: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);

    free(arr);
    fclose(fp);
}

void linear_search(int *arr, int arrsize, int key) {
    for (int i = 0; i < arrsize; ++i) {
        if (arr[i] == key) break;
    }
}