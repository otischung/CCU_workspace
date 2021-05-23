#include <stdio.h>
#define MaxLine 4096

// 回傳取完字元的位置
char *getUTF8Char(char *text, char *ch);


int main() {
    char line[MaxLine];
    char ch[8];
    unsigned char *ptr;

    while (fgets(line, MaxLine, stdin) != NULL) {
        ptr = line;
        while (ptr = getUTF8Char(ptr, ch)) {
            if (ch[0] == '\0') {
                fprintf(stderr, "illegal code\n");
            } else {
                printf("%s\n", ch);
            }
        }
    }

    return 0;
}


char *getUTF8Char(char *text, char *ch) {
    unsigned char *ptr, *qtr;

    if (*text == '\0') return NULL;

    ptr = text;
    qtr = ch;
    if (*ptr >= 0b11110000) {  // 240, 11110www 10xxxxxx 10yyyyyy 10zzzzzz
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b11100000) {  // 224, 1110xxxx 10yyyyyy 10zzzzzz
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b11000000) {  // 192, 110xxxxx 10yyyyyy
        *qtr++ = *ptr++;
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b11000000) {  // 128, error
        *ch = '\0';
        ++ptr;
    } else {  // ASCII
        *qtr++ = *ptr++;
        *qtr = '\0';
    }
    return ptr;
}
