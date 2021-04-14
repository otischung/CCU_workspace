#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *mystrcat(char *dest, char *source);

int main() {
    char input[1 << 14];
    char output[1 << 14];
    bool initial = false;
    while (fgets(input, 1 << 14, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        if (!initial) {
            strcpy(output, input);
            initial = true;
        } else {
            mystrcat(output, input);
        }
    }
    printf("%s\n", output);
    return 0;
}

char *mystrcat(char *dest, char *source) {
    char *ptr = dest;
    char *qtr = source;
    while (*ptr) ++ptr;
    while (*qtr) {
        *ptr++ = *qtr++;
    }
    *ptr = '\0';
    return ptr;
}