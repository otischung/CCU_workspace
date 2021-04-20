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
#define ARRSIZE 1024  // 2 ^ 10
// #define ARRSIZE 16777216  // 2 ^ 24


int main(int argc, char **argv) {
    srand(time(NULL));
    char *method;
    char **arr;
    struct timeval start, end;
    time_t diff;
    short mode; // 0: number, 1: A-Z, 2: a-z
    int fd;
    int lineLen;
    int i, j;

    gettimeofday(&start, NULL);
    arr = (char **)malloc(ARRSIZE * sizeof(char *));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }
    for (int i = 0; i < ARRSIZE; ++i) {
        arr[i] = (char *)malloc(128 * sizeof(char));
        if (arr[i] == NULL) {
            perror("malloc failed");
            return 1;
        }
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Malloc time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    gettimeofday(&start, NULL);
    for (i = 0; i < ARRSIZE; ++i) {
        lineLen = rand() % 125 + 2;
        for (j = 0; j < lineLen - 1; ++j) {
            mode = rand() % 3;
            switch (mode) {
                case 0:
                    arr[i][j] = rand() % 10 + '0';
                    break;
                case 1:
                    arr[i][j] = rand() % 26 + 'A';
                    break;
                case 2:
                    arr[i][j] = rand() % 26 + 'a';
                    break;
                default:
                    break;
            }
        }
        arr[i][j] = '\n';
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Generate random string time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    gettimeofday(&start, NULL);
    fd = open("./random_string.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    for (i = 0; i < ARRSIZE; ++i) {
        write(fd, arr[i], strlen(arr[i]));
        if (ARRSIZE % 1024 == 0) {
            fsync(fd);
        }
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("Write to file time: %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    close(fd);
    return 0;
}
