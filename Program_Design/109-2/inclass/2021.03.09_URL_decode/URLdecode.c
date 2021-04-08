#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxLineLen 4096

char *urlDecode(char *text);

int main() {
    char line[MaxLineLen];
    char *ptr, *qtr, *lineEnd, *last;
    int hex1, hex2;
    unsigned char c;

    while (fgets(line, MaxLineLen, stdin) != NULL) {
        ptr = line; last = line;  // init
        lineEnd = line + strlen(line);
        while (ptr != NULL) {
            ptr = strchr(ptr, '%');
            if (ptr == NULL) {  // There is no %
                qtr = last;
                while (qtr < lineEnd) {
                    putchar(*qtr++);
                }
                break;
            } else {  //You need to decode
                qtr = last;
                while (qtr < ptr) {
                    putchar(*qtr++);
                }
                ++ptr;  // point to the first hex bit.
                if (isdigit(*ptr)) {
                    hex1 = *ptr - '0';
                } else {
                    hex1 = *ptr - 'A' + 10;
                }
                ++ptr;  // point to the second hex bit.
                if (isdigit(*ptr)) {
                    hex2 = *ptr - '0';
                } else {
                    hex2 = *ptr - 'A' + 10;
                }
                c = (hex1 << 4) | hex2;
                putchar(c);
                ++ptr;  //decode complete.
                last = ptr;
            }
        }
    }
}