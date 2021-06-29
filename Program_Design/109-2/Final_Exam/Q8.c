#pragma GCC optimize ("O3")
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define STRICT 0
#define CASE 1
#define CNT 2
#define CASECNT 3

int main(int argc, char **argv) {
    short mode;
    char input[256];
    char *inptr;
    int cnt = 0;

    if (argc == 2) {
        mode = STRICT;
    } else if (argc == 3 && !strcmp(argv[1], "-i")) {
        mode = CASE;
    } else if (argc == 3 && !strcmp(argv[1], "-c")) {
        mode = CNT;
    } else if (argc == 4 && (!strcmp(argv[1], "-c") && !strcmp(argv[2], "-i") || (!strcmp(argv[1], "-i") && !strcmp(argv[2], "-c")))) {
        mode = CASECNT;
    } else {
        fprintf(stderr, "format error\n");
        exit(1);
    }

    while (fgets(input, 256, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }
        inptr = input;
        switch (mode) {
        case STRICT:
            if (strstr(input, argv[1]) != NULL) {
                printf("%s\n", input);
            }
            break;
        case CASE:
            if (strcasestr(input, argv[2]) != NULL) {
                printf("%s\n", input);
            }
        case CNT:
            while ((inptr = strstr(inptr, argv[2])) != NULL) {
                ++cnt;
                inptr += strlen(argv[2]);
            }
            break;
        case CASECNT:
            while ((inptr = strcasestr(inptr, argv[3])) != NULL) {
                ++cnt;
                inptr += strlen(argv[3]);
            }
            break;
        }
    }

    if (mode == CNT || mode == CASECNT) {
        printf("%d\n", cnt);
    }

    return 0;
}
