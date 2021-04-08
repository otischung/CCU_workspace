#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char **argv) {
    char exeBuf[4096];
    char *exename = basename(argv[0]);
    printf("%s\n", exename);
    system(exename);
    return 0;
}