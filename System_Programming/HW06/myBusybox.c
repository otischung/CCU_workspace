#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char **argv) {
    char exeBuf[4096];
    char *exename = basename(argv[0]);

    strcpy(exeBuf, exename);
    for (int i = 1; i < argc; ++i) {
        strcat(exeBuf, " ");
        strcat(exeBuf, argv[i]);
    }

    system(exeBuf);
    
    return 0;
}