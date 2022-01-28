#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define ENCODE 0
#define DECODE 1
#define unsigned long long llu

void swap(long double *x, long double *y);
void row_exchange(long double **arr, int x, int y, int columns);
void row_mult(long double **arr, int loc, int columns);
void row_add(long double **arr, int x, int y, int columns);

int main() {
    bool mode;          // encode or decode
    int chunks;         // divide input into # chunks
    int equations;      // create # equations
    char input[4096];   // input string
    long double **n_equations;  // input n_equations
    int chunk_length;   // the length of each chunk except the last one.
    int *n_chunks;      // store every number in chunks
    char *chunk_buf;    // buffer for atoi
    char *inptr;        // pointer of input string
    char *outptr;       // pointer of chunk buffer
    int sum;            // the sum of the argumented matrix

    scanf("%d %d", &mode, &chunks);
    if (mode == ENCODE) {  // ENCODE
        scanf("%d", &equations);
        scanf("%s", input);
        chunk_length = strlen(input) / chunks;
        n_chunks = (int *)calloc(chunks, sizeof(int));
        chunk_buf = (char *)calloc(chunk_length, sizeof(char));
        inptr = input;
        for (int i = 0; i < chunks; ++i) {  // Assume that strlen(input) % chunks == 0
            outptr = chunk_buf;
            for (int j = 0; j < chunk_length; ++j) {
                *outptr++ = *inptr++;
            }
            *outptr = '\0';
            n_chunks[i] = atoi(chunk_buf);
        }

        // for (int i = 0; i < chunks; ++i) {  // test
        //     printf("%d ", n_chunks[i]);
        // }
        // putchar('\n');

        for (int i = 0; i < chunks; ++i) {  // Identity Matrix
            for (int j = 0; j < chunks; ++j) {
                if (j == i) printf("1 ");
                else printf("0 ");
            }
            printf("%d\n", n_chunks[i]);
        }
        for (int i = 1; i <= equations; ++i) {  // Vandermonde matrix
            sum = 0;
            for (int j = 0; j < chunks; ++j) {
                sum += (int)(pow(i, j)) * n_chunks[j];
                printf("%d ", (int)(pow(i, j)));
            }
            printf("%d\n", sum);
        }

        free(n_chunks);
        free(chunk_buf);
    } else {  // DECODE
        n_equations = (long double **)calloc(chunks, sizeof(long double *));
        for (int i = 0; i < chunks; ++i) {
            n_equations[i] = (long double *)calloc(chunks + 1, sizeof(long double));
        }

        for (int i = 0; i < chunks; ++i) {
            for (int j = 0; j < chunks + 1; ++j) {
                scanf("%Lf", &n_equations[i][j]);
            }
        }

        // for (int i = chunks - 1; i > 0; --i) {  // bubble sort
        //     for (int j = 0; j < i; ++j) {
        //         if (n_equations[j][1] > n_equations[j + 1][1]) {
        //             row_exchange(n_equations, j, j + 1, chunks + 1);
        //         }
        //     }
        // }

        for (int i = 0; i < chunks; ++i) {  // Gauss-Jordan Elimination
            if (n_equations[i][i] == 0) {  // Find non-zero element to exchange
                int row_bias = 1;
                while ((i + row_bias) < chunks && n_equations[i + row_bias][i] == 0) {
                    ++row_bias;
                }
                if ((i + row_bias) == chunks) {
                    fprintf(stderr, "Can't find non-zero element.\n");
                    break;
                }
                row_exchange(n_equations, i, i + row_bias, chunks + 1);
            }
            for (int j = 0; j < chunks; ++j) {
                if (i != j) {
                    row_add(n_equations, i, j, chunks + 1);
                } else {
                    row_mult(n_equations, i, chunks + 1);
                }
            }
        }

        // for (int i = 0; i < chunks; ++i) {  // test
        //     for (int j = 0; j < chunks + 1; ++j) {
        //         printf("%Lf ", n_equations[i][j]);
        //     }
        //     putchar('\n');
        // }
        // putchar('\n');

        for (int i = 0; i < chunks; ++i) {
            printf("%d", (int)(n_equations[i][chunks] + 0.5));  // Round
        }
        putchar('\n');

        for (int i = 0; i < chunks; ++i) {
            free(n_equations[i]);
        }
        free(n_equations);
    }
    return 0;
}

void swap(long double *x, long double *y) {
    long double temp = *x;
    *x = *y;
    *y = temp;
}

void row_exchange(long double **arr, int x, int y, int columns) {
    for (int i = 0; i < columns; ++i) {
        swap(&arr[x][i], &arr[y][i]);
    }
    // printf("row exchange\n");  // test
    // for (int i = 0; i < columns - 1; ++i) {
    //     for (int j = 0; j < columns; ++j) {
    //         printf("%Lf ", arr[i][j]);
    //     }
    //     putchar('\n');
    // }
    // putchar('\n');
}

void row_mult(long double **arr, int loc, int columns) {
    long double mult = 1 / arr[loc][loc];
    for (int i = 0; i < columns; ++i) {
        arr[loc][i] *= mult;
    }
    // printf("row multi\n");  // test
    // for (int i = 0; i < columns - 1; ++i) {
    //     for (int j = 0; j < columns; ++j) {
    //         printf("%Lf ", arr[i][j]);
    //     }
    //     putchar('\n');
    // }
    // putchar('\n');
}

void row_add(long double **arr, int x, int y, int columns) {  // Add mult times of row x into row y
    long double mult = arr[y][x] / arr[x][x];
    for (int i = 0; i < columns; ++i) {
        arr[y][i] -= mult * arr[x][i];
    }
    // printf("row add\n");  // test
    // for (int i = 0; i < columns - 1; ++i) {
    //     for (int j = 0; j < columns; ++j) {
    //         printf("%Lf ", arr[i][j]);
    //     }
    //     putchar('\n');
    // }
    // putchar('\n');
}

/*
If you don't round your result, you will get the wrong answer, here is the example:
1 5
1 2 4 8 16 2368            
0 0 1 0 0 56                    
1 5 25 125 625 67582
1 3 9 27 81 10014
1 1 1 1 1 270

1234567889
*/
