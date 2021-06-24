// practice 2021.06.24
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *mystrstr(char *haystack, char *needle);
int mystrlen(const char *s);


////////////////////////////////////////////////////////////
int main() {
    char input[4096], line[4096], pattern[4096];
    char *inptr, *lineptr, *patptr, *lastlineptr;
    int patternLen;

    while (fgets(input, 4096, stdin) != NULL) {
        inptr = input;
        lineptr = line;
        patptr = pattern;
        while (*inptr != ',') {
            *lineptr++ = *inptr++;
        }
        *lineptr = '\0';
        ++inptr;
        while (*inptr && *inptr != '\n') {
            *patptr++ = *inptr++;
        }
        *patptr = '\0';

        inptr = input;
        lineptr = line;
        patptr = pattern;
        patternLen = mystrlen(pattern);
        lastlineptr = NULL;
        while ((lineptr = mystrstr(lineptr, patptr)) != NULL) {
            lastlineptr = lineptr;
            lineptr += patternLen;
        }
        if (lastlineptr == NULL) {
            printf("-1\n");
        } else {
            printf("%ld,%ld\n", lastlineptr - line, lastlineptr - line + patternLen - 1);
        }
    }
    return 0;
}
////////////////////////////////////////////////////////////


char *mystrstr(char *haystack, char *needle) {
    int needleLen;
    while (*haystack) {
        needleLen = 0;
        while (*haystack && *needle == *haystack) {
            ++needle;
            ++haystack;
            ++needleLen;
        }
        if (*needle == '\0') {
            return haystack - needleLen;
        } else {
            needle -= needleLen;
        }
        ++haystack;
    }
    return NULL;
}

int mystrlen(const char *s) {
    int len = 0;
    while (*s++) ++len;
    return len;
}
