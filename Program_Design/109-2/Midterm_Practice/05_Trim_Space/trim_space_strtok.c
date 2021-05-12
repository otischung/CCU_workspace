#include <stdio.h>
extern char* strtok(char* c, char *delm);
char* (*STRTOK)(char* c, char *delm) = strtok;

int main() {
    char buf[8192];
    char *delm = " \n\t";
    char *pch;
    while (fgets(buf, 8192, stdin) != NULL) {
        pch = STRTOK(buf, delm);
        while (pch != NULL) {
            printf("%s", pch);
            pch = STRTOK(NULL, delm);
            if (pch != NULL) putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}
