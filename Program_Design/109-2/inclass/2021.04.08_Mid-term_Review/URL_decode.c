#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MaxLine 4096

void urlDecode(char *);


///////////////////////////////////////////////////////////////////////
int main() {
    char line[MaxLine];

    while (fgets(line, MaxLine, stdin)) {
        urlDecode(line);
        printf("%s", line);
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////


void urlDecode(char *text) {
    char *p, *q, *last, *textEnd;
    char *tmpText;
    char h, l, v, c;
    int len;

    p = text;
    last = p;
    q = tmpText;
    tmpText = (char *)malloc(strlen(text) + 1);
    textEnd = text + strlen(text);

    while (p = strchr(p, '%')) {
        len = p - last;
        memcpy(q, last, len);
        ++p;
        if (isdigit(*p)) {
            h = *p - '0';
        } else {
            h = *p - 'A' + 10;
        }
        ++p;
        if (isdigit(*p)) {
            l = *p - '0';
        } else {
            l = *p - 'A' + 10;
        }

        v = (h << 4) | l;
        c = v & 255;
        *q++ = c;
        last = ++p;
    }
    len = textEnd - last;
    memcpy(q, last, len);
    strcpy(text, tmpText);
}