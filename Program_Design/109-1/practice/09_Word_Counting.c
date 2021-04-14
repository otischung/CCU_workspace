#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main() {
    int lineCnt = 0, wordCnt = 0, byteCnt = 0, longestLineLen = 0, longestWordLen = 0;
    int lineLen, wordLen = 0;
    bool inWord = false;
    char input[2048];
    char *ptr;
    while (fgets(input, 2048, stdin) != NULL) {
        ++lineCnt;
        lineLen = strlen(input);
        ptr = input;
        while (*ptr) {
            ++byteCnt;
            if (!isspace(*ptr)) {   // This is NOT a space.
                ++wordLen;
                if (!inWord) {      // The start of a word.
                    inWord = true;
                    ++wordCnt;
                }
                if (longestWordLen < wordLen) {
                    longestWordLen = wordLen;
                }
            } else {                // This is a space.
                if (inWord) {       // The end of a word.
                    inWord = false;
                    wordLen = 0;
                }
            }
            ++ptr;
        }
        if (longestLineLen < lineLen) {
            longestLineLen = lineLen;
        }
    }
    printf("Line count(s): %d\n", lineCnt);
    printf("Word count(s): %d\n", wordCnt);
    printf("Byte count(s): %d\n", byteCnt);
    printf("Longest line length: %d\n", longestLineLen);
    printf("Longest word length: %d\n", longestWordLen);
    return 0;
}