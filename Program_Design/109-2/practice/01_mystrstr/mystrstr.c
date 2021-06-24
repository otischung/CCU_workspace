#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *mystrstr(char *input, char *pattern);
bool match(char *input, char *pattern);


int main() {
    char buf[8192], input[4096], pattern[4096];
    int location;
    int patternLen;
    char *ptr, *qtr;

    while (fgets(buf, 8192, stdin) != NULL) {
        ptr = buf; qtr = input;
        while (*ptr != ',') {
            *qtr++ = *ptr++;
        }
        *qtr = '\0';
        ++ptr;
        qtr = pattern;
        while (*ptr != '\n') {
            *qtr++ = *ptr++;
        }
        *qtr = '\0';

        ptr = mystrstr(input, pattern);
        qtr = pattern;
        patternLen = 0;
        while (*qtr++) patternLen++;
        if (ptr) {
            location = (int)(ptr - input);
            printf("%d,%d\n", location, location + patternLen - 1);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}


char *mystrstr(char *input, char *pattern) {
    char *ptr, *qtr;
    int inputLen, patternLen;

    ptr = input;
    qtr = pattern;
    inputLen = 0;
    patternLen = 0;

    while (*ptr++) inputLen++;
    while (*qtr++) patternLen++;
    ptr -= patternLen;
    qtr = pattern;

    while (ptr >= input) {
        if (match(ptr, qtr)) {
            return ptr;  // break
        }
        --ptr;
    }
    // printf("%d\n%d\n", inputLen, patternLen);
    if (ptr < input) return NULL;
}

bool match(char *input, char *pattern) {
    while (*pattern) {
        if (*input++ != *pattern++) {
            return false;
        }
    }
    return true;
}