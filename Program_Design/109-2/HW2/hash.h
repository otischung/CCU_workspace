#pragma once
#include "randint_gen.h"

typedef struct HASHNODE {
    int key;
    struct HASHNODE *next;
} HN;

static void hash(int arrsize, int query);
static inline unsigned long long key2addr(int arrsize, int key);
static bool find(HN **arr, int arrsize, int key);
static void freehashll(HN *head);
static bool hash_free(HN **arr, int arrsize);

///////////////////////////////////////////////////////////////////////////////////////
static void hash(int arrsize, int query) {
    FILE *fp;
    HN **arr;
    int num, collision = 0;
    unsigned long long addr;
    struct timespec start, end;
    time_t diff;

    fp = fopen("./randint.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }
    printf("hash:\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    arr = (HN **)calloc(arrsize << 1, sizeof(HN *));
    for (int i = 0; i < arrsize; ++i) {
        HN *newNode = (HN *)malloc(sizeof(HN));
        newNode->next = NULL;
        fscanf(fp, "%d", &num);
        newNode->key = num;
        addr = key2addr(arrsize << 1, num);
        // if (addr < 0) addr *= -1;
        if (arr[addr] == NULL) arr[addr] = newNode;
        else {
            ++collision;
            HN *traverse = arr[addr];
            while (traverse->next != NULL) {
                traverse = traverse->next;
            }
            traverse->next = newNode;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Hash collision: %d\n", collision);
    printf("Time for insert key to hashtable: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);
    num = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < query; ++i) {
        if (find(arr, arrsize << 1,  rand())) {
            ++num;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("We have found %d keys.\n", num);
    printf("Time for searching keys to hashtable: %ldns = %.2lfs\n\n", diff, (double)diff / 1000000000.0);

    hash_free(arr, arrsize << 1);
    fclose(fp);
}
///////////////////////////////////////////////////////////////////////////////////////

static inline unsigned long long key2addr(int arrsize, int key) {
    unsigned long long addr = 2166136261;
    // addr = key - (1 << 30);  // hash(x) = (x - INT_MAX / 2) ^ 2
    // addr *= addr;

    /*        FNV-1a algorithm        */
    addr ^= key;
    addr *= 16777619;
    addr %= arrsize;
    // reference: https://reurl.cc/NX5Nvp
    return addr;
}

static bool find(HN **arr, int arrsize, int key) {
    unsigned long long addr = key2addr(arrsize, key);
    HN *traverse = arr[addr];
    if (traverse == NULL) return false;
    else {
        while (traverse) {
            if (traverse->key == key) {
                // printf("%d is found.\n", key);
                return true;
            }
            traverse = traverse->next;
        }
        return false;
    }
}

static void freehashll(HN *head) {
    HN *pre, *cur;
    cur = head;
    while (cur) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
}

static bool hash_free(HN **arr, int arrsize) {
    for (int i = 0; i < arrsize; ++i) {
        if (arr[i] != NULL) {
            freehashll(arr[i]);
        }
    }
    free(arr);
}
