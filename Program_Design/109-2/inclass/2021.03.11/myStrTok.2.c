#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxLine 4096

char *getTerm(char *text, char *term, char *delim);
char *isdelimiter(char delim);

int main() {
    char line[MaxLine];
    char *ptr, *qtr, *textEnd, *term;
    char delim[] = " \t,.;[]()@#$";

    // term haven't been malloc.

    while (fgets(line, MaxLine, stdin) != NULL) {
        ptr = line;
        while (ptr) {
            ptr = getTerm(ptr, term, delim);
            printf("%s\n", term);
        }
    }
    return 0;
}

char *getTerm(char *text, char *term, char *delim) {
    char *ptr = text;
    char *qtr = term;

    // skip delims
    // while (isdelimiter(*ptr)) ++ptr;
    while (strchr(delim, *ptr)) ++ptr;
    // while (!isdelimiter(*ptr) && *ptr) *qtr++ = *ptr++;
    while (!strchr(delim, *ptr) && *ptr) *qtr++ = *ptr++;
    *qtr = '\0';
    // check ending conditterm[0] == '\0'ion
    if (term[0] == '\0') return NULL;
    // if (qtr == term) return NULL;
    else return ptr;
}