#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main() {
    char input[2048];
    char *ptr;

    while (fgets(input, 2048, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] =  '\0';
        
        ptr = input;

        while (*ptr) {
            if (*ptr < 0) {
                for (int i = 0; i < 3; ++i) {
                    putchar(*ptr++);
                }
                putchar('\n');
            } else if (*ptr == ' ') {
                ++ptr;
            } else {
                while (*ptr && *ptr != ' ') {
                    putchar(*ptr++);
                }
                putchar('\n');
            }
        }
        // if (*(ptr - 1) > 0) putchar('\n');
    }
    return 0;
}