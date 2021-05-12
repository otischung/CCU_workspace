#include <stdio.h>
#include <stdlib.h>
#define MaxWordLen 1024

char *ltrim(char *s) {
    while (*s == ' ') ++s;
    return s;
}

char *rtrim(char *s) {
    char *ptr = s;
    while (*ptr != '\n') ++ptr;
    --ptr;
    while (*--ptr == ' ');
    *ptr++ = '\n';
    *ptr = '\0';
    return s;
}

void trim(char *s) {
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
}

int main() {
    char input[MaxWordLen];

    while (fgets(input, MaxWordLen, stdin) != NULL) {
        printf("%s", rtrim(ltrim(input)));
        // trim(input);
        // printf("%s", input);
    }

    return 0;
}
