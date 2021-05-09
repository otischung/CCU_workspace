#pragma once
#include "randint_gen.h"

typedef struct LLNODE {
    int key;
    struct LLNODE *next;
} LLNode;

static void linked_list(int arrsize, int query);
static LLNode *ll_insert(LLNode *head, int key);
static bool ll_find(LLNode *head, int key);
static void ll_print(LLNode *head);
static void freell(LLNode *head);

///////////////////////////////////////////////////////////////
static void linked_list(int arrsize, int query) {
    FILE *fp;
    int num;
    struct timespec start, end;
    time_t diff;

    fp = fopen("./randint.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }
    printf("ll:\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    LLNode *head = NULL;
    for (int i = 0; i < arrsize; ++i) {
        fscanf(fp, "%d", &num);
        head = ll_insert(head, num);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for insert key to linked list: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);
    num = 0;

    // ll_print(head);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < query; ++i) {
        if (ll_find(head, rand())) {
            ++num;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("We have found %d keys.\n", num);
    printf("Time for search in linked list: %ldns = %.2lfs\n\n", diff, (double)diff / 1000000000.0);

    freell(head);
    fclose(fp);
}
///////////////////////////////////////////////////////////////

static LLNode *ll_insert(LLNode *head, int key) {
    LLNode *newLLNode = (LLNode *)malloc(sizeof(LLNode));
    newLLNode->key = key;
    newLLNode->next = NULL;
    
    if (head == NULL) {
        return newLLNode;
    } else {
        newLLNode->next = head;
        return newLLNode;
    }
}

static bool ll_find(LLNode *head, int key) {
    LLNode *traverse = head;
    while (traverse) {
        if (traverse->key == key) {
            // printf("%d is found.\n", key);
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

static void ll_print(LLNode *head) {
    LLNode *traverse = head;
    while (traverse) {
        printf("%d\n", traverse->key);
        traverse = traverse->next;
    }
}

static void freell(LLNode *head) {
    LLNode *pre, *cur;
    cur = head;
    while (cur) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
}
