#pragma once
#include "randint_gen.h"

void hash(int arrsize, int query) {
    FILE *fp;
    int num;
    struct timespec start, end;
    time_t diff;

    fp = fopen("./randint.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }

    fclose(fp);
}
