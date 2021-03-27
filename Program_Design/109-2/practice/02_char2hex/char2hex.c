#pragma GCC diagnostic ignored "-Wpointer-sign"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE (1 << 16)

int main() {
    unsigned char input[BUF_SIZE];
    unsigned char output[BUF_SIZE];
    unsigned char *ptr, *qtr;

    while ((fgets(input, BUF_SIZE, stdin)) != NULL) {
        ptr = input; qtr = output;
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';
        
        while (*ptr != '\0') {
            if (( *ptr >= 'A' && *ptr <= 'Z')\
              || (*ptr >= 'a' && *ptr <= 'z')\
              || (*ptr >= '0' && *ptr <= '9')\
              ||  *ptr == '.')                 {
                  *qtr++ = *ptr++;
            } else {
                *qtr++ = '%';
                sprintf(qtr, "%X", *ptr);
                ++ptr; qtr += 2;
            }
        }
        *qtr = '\0';
        printf("%s\n", output);
    }

    return 0;
}