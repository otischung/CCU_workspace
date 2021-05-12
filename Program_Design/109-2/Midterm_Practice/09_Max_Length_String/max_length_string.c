#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[8192] = "";
    char maxword[1024] = "";
    char delim[] = ", .\n";
    char *strptr;

    while (fgets(input, 8192, stdin) != NULL) {
        memset(maxword, 0, sizeof(char));
        strptr = strtok(input, delim);
        if (strlen(maxword) < strlen(strptr)) strcpy(maxword, strptr);
        while (strptr) {
            if (strlen(maxword) < strlen(strptr)) strcpy(maxword, strptr);
            strptr = strtok(NULL, delim);
        }
        printf("%s\n", maxword);
    }

    return 0;
}
