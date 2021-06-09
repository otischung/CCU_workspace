#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[2048];
    char *ptr;

    while (fgets(input, 2048, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] =  '\0';
        
        ptr = input;
        while (*ptr) {
            if (*ptr == '\"') {
                ++ptr;
                while (*ptr && *ptr != '\"') {
                    putchar(*ptr++);
                }
                ++ptr;
                putchar('\n');
            } else {
                ++ptr;
            }
        }
    }

    return 0;
}
