#pragma once
#include "randint_gen.h"

static void binary_search(int arrsize, int query);
static int cmp(const void *a, const void *b);
static bool bs(int *arr, int arrsize, int key);

static void binary_search(int arrsize, int query) {
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
    printf("bs:\n");

    // cpu_threads = sysconf(_SC_NPROCESSORS_CONF);
    // task = (pthread_t *)calloc(cpu_threads, sizeof(pthread_t));
    
    clock_gettime(CLOCK_MONOTONIC, &start);
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
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for insert key to array: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);

    clock_gettime(CLOCK_MONOTONIC, &start);
    qsort(arr, arrsize, sizeof(arr[0]), cmp);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for qsort: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);

    num = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < query; ++i) {
        if (bs(arr, arrsize, rand())) {
            ++num;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("We have found %d keys.\n", num);
    printf("Time for binary search to array: %ldns = %.2lfs\n\n", diff, (double)diff / 1000000000.0);

    free(arr);
    fclose(fp);
}

static int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

static bool bs(int *arr, int arrsize, int key) {
    int left, mid, right;
    left = 0;
    right = arrsize - 1;

    while (left < right - 1) {
        mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            printf("%d is found.\n", key);
            return true;
        }
        else if (arr[mid] < key) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if (arr[right] == key) {
        printf("%d is found.\n", key);
        return true;
    }
    return false;
}