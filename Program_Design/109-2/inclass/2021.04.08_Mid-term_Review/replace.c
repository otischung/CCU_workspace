#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MaxLine 4096

void replace(char *, char *, char *);


///////////////////////////////////////////////////////////////////////
int main() {
    char srcPat[] = "apple";
    char targetPat[] = "banana";
    char line[MaxLine];
    char longestLine[MaxLine];
    int len;

    while (fgets(line, MaxLine, stdin) != NULL) {
        if (strstr(line, srcPat)) {
            replace(line, srcPat, targetPat);
            printf("%s", line);
        }
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////


void replace(char *line, char *s, char *t) {
    char *p, *q, *last, tmpLine;
    int tmpLen, sLen, tLen;

    q = tmpLine;
    sLen = strlen(s);
    tLen = strlen(t);
    tmpLen = strlen(line) * ((float)tLen / sLen);
    // tmpLine = (char *)malloc(...);
    

    p = line;
    last = p;

    while (p = strstr(p, s)) {
        int len = p - last;
        memcpy(q, last, len);
        q += len;
        memcpy(q, t, tLen);
        p += sLen;
        last = p;
    }
}