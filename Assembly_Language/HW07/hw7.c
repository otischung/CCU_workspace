#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    FILE *input, *output;
    struct timespec start, end, use;
    float a[200][198];
    float b[200][198];
    float c[200];

OPEN_DATA:
    input = fopen("data.txt", "r");
    if (input == NULL) {
        if (access("data.txt", F_OK) == -1 && access("gen_float", F_OK) == 0) {
            fprintf(stderr, "Find gen_float\n");
            system("./gen_float");
            goto OPEN_DATA;
        } else if (access("Makefile", F_OK) == 0 || access("makefile", F_OK) == 0) {
            fprintf(stderr, "Find Makefile\n");
            system("make -j");
            goto OPEN_DATA;
        } else if (access("Makefile", F_OK) != 0 && access("makefile", F_OK) != 0) {
            fprintf(stderr, "Missing Makefile\n");
            if (access("gen_float.c", F_OK) == 0) {
                fprintf(stderr, "Find 'gen_float.c', use it to create data.txt\n");
                system("gcc -g -mavx gen_float.c -o gen_float");
                system("./gen_float");
                goto OPEN_DATA;
            } else if (access("gen_int_10", F_OK) == 0) {
                fprintf(stderr, "Find 'gen_int_10.c', use it to create data.txt\n");
                system("gcc -g -mavx gen_int_10.c -o gen_int_10");
                system("./gen_int_10");
                goto OPEN_DATA;
            } else {
                fprintf(stderr, "Error, can't find sorce code to make data.txt\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Can't open data.txt\n");
            exit(1);
        }
    }
    output = fopen("output.txt", "w+");
    if (output == NULL) {
        fprintf(stderr, "Can't open output_simd.txt\n");
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < 198; ++j) {
            fscanf(input, "%f", &a[i][j]);
        }
    }
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < 198; ++j) {
            fscanf(input, "%f", &b[i][j]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Read data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 200; ++i) {
        c[i] = 0.0;
        for (int j = 0; j < 200; ++j) {
            for (int k = 0; k < 198; ++k) {
                c[i] += a[i][k] * b[j][k];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Compute data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 200; ++i) {
        fprintf(output, "%f\n", c[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Write data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    fclose(output);
    fclose(input);
}
