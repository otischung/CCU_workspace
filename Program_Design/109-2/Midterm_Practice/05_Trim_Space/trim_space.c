#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxWordLen 1024

char *ltrim(char *s) {
    while (*s == ' ') ++s;
    return s;
}

char *rtrim(char *s) {
    char *ptr = s;
    while (*ptr != '\n') ++ptr;
    while (isspace(*--ptr));
    *++ptr = '\n';
    *++ptr = '\0';
    return s;
}

char *trim(char *s) {
    char output[MaxWordLen];
    char *ptr, *qtr;

    s = rtrim(ltrim(s));
    ptr = s;
    qtr = output;

    while (*ptr != '\n') {
        if (*ptr != ' ') *qtr++ = *ptr++;
        else {
            *qtr++ = *ptr++;
            while (*ptr == ' ' && *ptr != '\n') ++ptr;
        }
    }
    *qtr = '\0';
    ptr = s;
    qtr = output;

    while (*qtr) {
        *ptr++ = *qtr++;
    }
    *ptr++ = '\n';
    *ptr = '\0';
    return s;
}

int main() {
    char input[MaxWordLen];
    char *inputptr;

    while (fgets(input, MaxWordLen, stdin) != NULL) {
        inputptr = input;
        inputptr = trim(inputptr);
        printf("%s", inputptr);
    }

    return 0;
}
