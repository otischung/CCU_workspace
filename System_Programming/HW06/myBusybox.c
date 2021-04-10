#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#define MaxBufLen 4096

int main(int argc, char **argv) {
    char exeBuf[MaxBufLen];
    char *exename = basename(argv[0]);
    int inputLen = MaxBufLen;

    strcpy(exeBuf, exename);
    inputLen -= strlen(exename);
    for (int i = 1; i < argc; ++i) {
        strcat(exeBuf, " ");
        strcat(exeBuf, argv[i]);
        inputLen -= (strlen(argv[i]) + 1);
        if (inputLen < 0) {
            fprintf(stderr, "Too long\nMax buffer len is %d\n", MaxBufLen);
            return 1;
        }
    }

    system(exeBuf);
    
    return 0;
}
