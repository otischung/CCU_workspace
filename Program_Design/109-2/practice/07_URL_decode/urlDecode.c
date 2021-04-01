#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxInputLen 8192
#define MaxOutputLen 8192

int main() {
    char input[MaxInputLen];
    char output[MaxOutputLen];
    char *inputptr, *inputEnd, *lastinputptr, *rwptr;
    char *outputptr;
    int hex1, hex2;
    bool error;
    unsigned char c;

    while (fgets(input, MaxInputLen, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] =  '\0';
        }

        inputptr = input; lastinputptr = input;  // init
        inputEnd = input + strlen(input);
        outputptr = output;

        while (inputptr != NULL) {
            inputptr = strchr(inputptr, '%');
            if (inputptr == NULL) {  // There is no %
                rwptr = lastinputptr;
                while (rwptr < inputEnd) {
                    *outputptr++ = *rwptr++;
                }
                break;
            } else {  //You need to decode
                rwptr = lastinputptr;
                while (rwptr < inputptr) {
                    *outputptr++ = *rwptr++;
                }
                ++inputptr;  // point to the first hex bit.
                if (isdigit(*inputptr)) {
                    hex1 = *inputptr - '0';
                } else if (*inputptr >= 'A' && *inputptr <= 'F') {
                    hex1 = *inputptr - 'A' + 10;
                } else {
                    fprintf(stderr, "error format\n");  // In Juice judge, you have to print to stdout.
                    error = true;
                    break;
                }
                ++inputptr;  // point to the second hex bit.
                if (isdigit(*inputptr)) {
                    hex2 = *inputptr - '0';
                } else if (*inputptr >= 'A' && *inputptr <= 'F') {
                    hex2 = *inputptr - 'A' + 10;
                } else {
                    fprintf(stderr, "error format\n");  // In Juice judge, you have to print to stdout.
                    error = true;
                    break;
                }

                c = (hex1 << 4) | hex2;
                *outputptr++ = (char)c;
                ++inputptr;  //decode complete.
                lastinputptr = inputptr;
            }
        }

        if (error) {
            error = false;
            continue;
        } else {
            *outputptr = '\0';
            printf("%s\n", output);
        }

        input[0] = '\0'; output[0] = '\0';
    }

    return 0;
}