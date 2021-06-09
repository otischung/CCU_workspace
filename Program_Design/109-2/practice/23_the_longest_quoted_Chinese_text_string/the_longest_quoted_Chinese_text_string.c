#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/********************************
 * 「 = -29 -128 -116, E3 80 8C
 * 」 = -29 -128 -115, E3 80 8D
 * 『 = -29 -128 -114, E3 80 8E
 * 』 = -29 -128 -113, E3 80 8F
*********************************/
int main() {
    char input[2048];
    char buf[2048];
    char *inputptr, *bufptr;
    char longest[2048] = "";
    int buflen = 0, longestlen = 0;

    while (fgets(input, 2048, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] =  '\0';
        
        inputptr = input;
        bufptr = buf;
        while (*inputptr) {
            if ((*inputptr == -29 && *(inputptr + 1) == -128 && *(inputptr + 2) == -116) ||\
                (*inputptr == -29 && *(inputptr + 1) == -128 && *(inputptr + 2) == -114)) {  // 「 or 『
                inputptr += 3;
                while (*inputptr &&\
                      !(*inputptr == -29 && *(inputptr + 1) == -128 && *(inputptr + 2) == -115) &&\
                      !(*inputptr == -29 && *(inputptr + 1) == -128 && *(inputptr + 2) == -113)) {  // 」 or 』
                    *bufptr++ = *inputptr++;
                }
                inputptr += 3;
                *bufptr++ ='\n';
                *bufptr ='\0';
            } else {
                ++inputptr;
            }
        }
        // printf("%s", buf);

        buflen = strlen(buf);
        if (longestlen < buflen) {
            strcpy(longest, buf);
            longestlen = buflen;
        }
        memset(buf, 0, buflen * sizeof(char));
    }

    printf("%s", longest);

    return 0;
}
