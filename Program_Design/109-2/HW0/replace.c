#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    bool wordMatch = false;
    char input[4096];
    char output[4096];
    char *pre, *cur, *last, *inputptr, *outputptr,  *targetptr, *replaceptr;
    int targetLen, replaceLen;

    if (argc == 4 && !strcmp(argv[1], "-e")) {
        wordMatch = true;
    } else if ((argc == 4 && strcmp(argv[1], "-e") && strcmp(argv[1], "-s")) || (argc != 3 && argc != 4)) {
        fprintf(stdout, "選項錯誤\n");
        return 0;
    }

    while (fgets(input, 4096, stdin) != NULL) {
        pre = input; cur = input; inputptr = input; // Initialize.
        last = input + strlen(input);
        outputptr = output;
        if (argc == 3) {
            targetptr = argv[1];
            replaceptr = argv[2];
        } else {
            targetptr = argv[2];
            replaceptr = argv[3];
        }
        targetLen = strlen(targetptr);
        replaceLen = strlen(replaceptr);

        while ((cur = strstr(cur, targetptr)) != NULL) {
            // printf("%d %d\n", isspace(*(cur + targetLen)), isspace(*(cur - 1)));
            // printf("%d %d\n", *(cur + targetLen),*(cur - 1));
            // 這個判斷我真的不行
            if (((!isspace(*(cur + targetLen)) && *(cur + targetLen) != 0) || (!isspace(*(cur - 1)) && *(cur - 1) != 0)) && wordMatch) {
                // Skip this word.
                cur += targetLen;
                continue;
            }
            while (pre != cur) {
                *outputptr++ = *pre++;
            }
            *outputptr = *pre;
            cur += strlen(targetptr);
            for (int i = 0; i < replaceLen; ++i) {
                *outputptr++ = *replaceptr++;
            }
            if (argc == 3) {
                targetptr = argv[1];
                replaceptr = argv[2];
            } else {
                targetptr = argv[2];
                replaceptr = argv[3];
            }
            pre = cur;
        }
        while (pre != last) {
            *outputptr++ = *pre++;
        }
        *outputptr = *pre;
        printf("%s", output);
        memset(input, '\0', sizeof(char) * 4096);
        memset(output, '\0', sizeof(char) * 4096);
    }
    return 0;
}