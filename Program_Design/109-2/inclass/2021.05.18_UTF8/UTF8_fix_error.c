// ./bin/garbled_text_generator < test.txt | ./bin/UTF8_fix_error
// 照理說應該要是清除規則外的字元，然後再重新解釋，這裡只做 skip
// 所以，如果資料嚴重毀損，將無法修復
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
                continue;
            } else {
                printf("%s", ch);
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
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b11100000) {  // 224, 1110xxxx 10yyyyyy 10zzzzzz
        *qtr++ = *ptr++;
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b11000000) {  // 192, 110xxxxx 10yyyyyy
        *qtr++ = *ptr++;
        if (*ptr < 0b10000000 || *ptr > 0b10111111) { ch[0] = '\0'; return ++ptr; }
        *qtr++ = *ptr++;
        *qtr = '\0';
    } else if (*ptr >= 0b10000000) {  // 128, error
        *ch = '\0';
        ++ptr;
    } else {  // ASCII
        *qtr++ = *ptr++;
        *qtr = '\0';
    }
    return ptr;
}
