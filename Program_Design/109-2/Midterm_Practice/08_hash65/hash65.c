#include <stdio.h>
#include <string.h>

int main() {
    char input[8];
    char *ptr;
    unsigned long long hv = 0;

    while (fgets(input, 8, stdin) != NULL) {
        hv = 0;
        if (input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] =  '\0';
        }
        ptr = input;
        while (*ptr) {
            hv = hv * 65 + *ptr++;
        }
        printf("%llu\n", hv);
    }

    return 0;
}
