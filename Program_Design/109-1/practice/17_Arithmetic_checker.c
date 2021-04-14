#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define ADD 1
#define MINUS 0

bool iscorrect(char *formula);
void reset(char *numbuf, bool *innum, short *numlen);

int main() {
    char input[1024];
    int correctCnt = 0;
    bool correct;

    while (fgets(input, 1024, stdin) != NULL) {
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        correct = iscorrect(input);
        if (correct) {
            ++correctCnt;
        }
    }
    printf("Correct : %d\n", correctCnt);
    return 0;
}

bool iscorrect(char *formula) {
    char numbuf[128];
    short numlen = 0;
    char *ptr = formula;
    double ans = 0, phasenum;
    bool init = false;
    bool innum = false;
    bool mode;

    do {
        if (isdigit(*ptr) || *ptr == '-' || *ptr == '.') {
            numbuf[numlen++] = *ptr;
            innum = true;
            if (*ptr == '-' && !isdigit(*(ptr + 1))) {
                reset(numbuf, &innum, &numlen);
            }
        } else if (isspace(*ptr)) {
            if (innum) {
                phasenum = atof(numbuf);
                reset(numbuf, &innum, &numlen);
                if (!init) {
                    ans += phasenum;
                    init = true;
                } else if (mode == ADD) {
                    ans += phasenum;
                } else if (mode == MINUS) {
                    ans -= phasenum;
                }
            }
        }
        if (*ptr == '+') {
            mode = ADD;
        } else if (*ptr == '-') {
            mode = MINUS;
        }
    } while (*ptr++ != '=');

    do {
        if (isdigit(*ptr) || *ptr == '-' || *ptr == '.') {
            numbuf[numlen++] = *ptr;
            innum = true;
        } else if (isspace(*ptr) || *ptr == '\0') {
            if (innum) {
                phasenum = atof(numbuf);
                reset(numbuf, &innum, &numlen);
            }
        }
    } while (*ptr++);

    if (phasenum == ans) return true;
    else return false;
}

void reset(char *numbuf, bool *innum, short *numlen) {
    *innum = false;
    *numlen = 0;
    memset(numbuf, 0, sizeof(char) * 128);
}