#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxLineLen 2048

void mystrtok(char *line, char *pattern);


//////////////////////////////////////////////////
int main() {
    char line[MaxLineLen];
    char pattern[MaxLineLen];

    while (~scanf("%s %s", line, pattern)) {
        mystrtok(line, pattern);
        putchar('\n');
    }

    return 0;
}
//////////////////////////////////////////////////


void mystrtok(char *line, char *pattern) {
    char split[MaxLineLen];
    bool first = true;
    bool empty = true;
    bool find = false;
    char *lineptr = line;
    char *prelineptr = NULL;
    char *linelast = line + strlen(line) - 1;
    char *splitptr;
    int patternLen = strlen(pattern);

    while ((lineptr = strstr(lineptr, pattern)) != NULL) {
        find = true;
        splitptr = split;
        while (line < lineptr) {
            empty = false;
            *splitptr++ = *line++;
        }
        *splitptr = '\0';
        if (strcmp(split, "\0")) {
            if (first) {
                printf("%s", split);
                first = false;
            } else {
                printf(",%s", split);
            }
        }

        lineptr += patternLen;
        line += patternLen;
        prelineptr = lineptr;
    }
    if (!find) {
        printf("%s", line);
        return;
    }
    splitptr = split;
    while (prelineptr <= linelast) {
        empty = false;
        *splitptr++ = *prelineptr++;
    }
    *splitptr = '\0';
    if (strcmp(split, "\0")) {
        if (first) {
            printf("%s", split);
            first = false;
        } else {
            printf(",%s", split);
        }
    }
    if (empty) {
        printf("empty string");
    }
}