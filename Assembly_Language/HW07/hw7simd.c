#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    FILE *input, *output;
    struct timespec start, end, use;
    float A[200][200] __attribute__((aligned(32)));
    float B[200][200] __attribute__((aligned(32)));
    float R[8] __attribute__((aligned(32)));
    float TMP[8] __attribute__((aligned(32)));
    float S[200];
    __m256 *a, *b, *t, *r;
    int i, j, k;

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
    output = fopen("output_simd.txt", "w+");
    if (output == NULL) {
        fprintf(stderr, "Can't open output_simd.txt\n");
        exit(1);
    }

    for (i = 0; i < 200; ++i) {
        A[i][198] = 0.0;
        A[i][199] = 0.0;
        B[i][198] = 0.0;
        B[i][199] = 0.0;
    }
    memset(S, 0, 200 * sizeof(float));

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < 200; ++i) {
        for (j = 0; j < 198; ++j) {
            fscanf(input, "%f", &A[i][j]);
        }
    }
    for (i = 0; i < 200; ++i) {
        for (j = 0; j < 198; ++j) {
            fscanf(input, "%f", &B[i][j]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Read data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    // Use intrinsic functions

    t = (__m256 *)TMP;
    r = (__m256 *)R;
    for (i = 0; i < 200; ++i) {
        *r = _mm256_setzero_ps();
        a = (__m256 *)A[i];
        for (j = 0; j < 200; ++j) {
            b = (__m256 *)B[j];
            for (k = 0; k < 25; ++k) {
                *t = _mm256_mul_ps(a[k], b[k]);
                *r = _mm256_add_ps(*r, *t);
            }
        }
        // for (j = 0; j < 8; ++j) {
        //     S[i] += R[j];
        // }
        *r = _mm256_hadd_ps(*r, *r);  // [7:0] = [6+7, 4+3, 6+7, 4+3, 2+3, 0+1, 2+3, 0+1]
        *r = _mm256_hadd_ps(*r, *r);  // [8:1] = [4~7, 4~7, 4~7, 4~7, 0~3, 0~3, 0~3, 0~3], 0~3 means 0+1+2+3
        S[i] += R[0] + R[4];
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Compute data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 200; ++i) {
        fprintf(output, "%f\n", S[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    use.tv_sec = end.tv_sec - start.tv_sec;
    use.tv_nsec = end.tv_nsec - start.tv_nsec;
    printf("Write data time: %ldns\n", use.tv_sec * (long)1e9 + use.tv_nsec);

    fclose(output);
    fclose(input);
}
