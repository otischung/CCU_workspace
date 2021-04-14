// Last edit: 2020.11.25 00:29
#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define inputlength 128
#define student 256
#define namelength 32
#define INSERT 0
#define DELETE 1
#define QUERY 2
#define PRINT 3
#define SORT 4
#define ERROR -1

char stu[student][namelength];
int math[student];
int eng[student];
int prog[student];
int size;

char **getword(char **ptrloc, char *word);
int phrase(char **ptrloc);
bool insert(char **ptrloc);
bool print(char **ptrloc);
bool query(char **ptrloc);
bool delete(char **ptrloc);
bool sort(char **ptrloc);

int main() {
    for (int i = 0; i < student; ++i) {
        math[i] = -1; eng[i] = -1; prog[i] = -1;
    }
    size = 0;

    char command[inputlength];
    char *ptr = command;
    int mode = -1;
    bool format;
    while (fgets(command, inputlength, stdin)) {
        mode = phrase(&ptr);
        if (mode == ERROR) {
            printf("format error, please re-enter.\n");
            ptr = command;
            continue;
        }
        if (mode == INSERT) {
            format = insert(&ptr);
            if (!format) {
                printf("format error, please re-enter.\n");
                mode = ERROR;
                ptr = command;
                continue;
            }
        } else if (mode == PRINT) {
            format = print(&ptr);
            if (!format) {
                printf("format error, please re-enter.\n");
                mode = ERROR;
                ptr = command;
                continue;
            }
        } else if (mode == QUERY) {
            format = query(&ptr);
            if (!format) {
                printf("format error, please re-enter.\n");
                mode = ERROR;
                ptr = command;
                continue;
            }
        } else if (mode == DELETE) {
            format = delete(&ptr);
            if (!format) {
                printf("format error, please re-enter.\n");
                mode = ERROR;
                ptr = command;
                continue;
            }
        } else if (mode == SORT) {
            format = sort(&ptr);
            if (!format) {
                printf("format error, please re-enter.\n");
                mode = ERROR;
                ptr = command;
                continue;
            }
        } else {
            printf("format error, please re-enter.\n");
            ptr = command;
            continue;
        }
        ptr = command;
    }
    
    return 0;
}

///////////////////////////////////////////////////////////////

int phrase(char **ptrloc) {
    char mode[inputlength];
    ptrloc = getword(ptrloc, mode);
    if (!strcmp(mode, "i")) return INSERT;
    else if (!strcmp(mode, "d")) return DELETE;
    else if (!strcmp(mode, "q")) return QUERY;
    else if (!strcmp(mode, "p")) return PRINT;
    else if (!strcmp(mode, "s")) return SORT;
    else return ERROR;
}

char **getword(char **ptrloc, char *word) {
    char **ptr = ptrloc;
    char *qtr = word;

    while (**ptr && isspace(**ptr)) {     // Skip space characters.
        ++(*ptr);
    }

    while (**ptr && !isspace(**ptr)) {    // Get a word into word[].
        if (qtr - word > inputlength) {
            fprintf(stderr, "Input length is too long.\n");
            break;
        }
        *qtr = **ptr;    // Copy one word into word.
        ++qtr; ++(*ptr);
    }
    *qtr = '\0';    // The end of the word.
    
    if (qtr - word == 0) {  // No more words to get.
        return NULL;    // Let the loop function stop. End of getword.
    } else {
        return ptr;     // Let ptr point to the space of the next word, and continue the loop.
    }
}

bool insert(char **ptrloc) {
    char nametmp[inputlength];
    char scoretmp[inputlength];
    char score[inputlength];
    bool m = 0, e = 0, p = 0;
    ptrloc = getword(ptrloc, nametmp);
    // printf("%s\n", nametmp);
    if (nametmp[0] != 'n' || nametmp[1] != ':') {
        return 0;
    } else {
        if (strcmp(nametmp, "n:") == 0) return 0;
        char *ptr = &nametmp[2];
        char *qtr = stu[size];
        while (*ptr) {
            *qtr++ = *ptr++;
        }
        *qtr = '\0';
        while (ptrloc = getword(ptrloc, scoretmp)) {
            // printf("%s\n", scoretmp);
            if ((scoretmp[0] != 'm' && scoretmp[0] != 'e' && scoretmp[0] != 'p') || scoretmp[1] != ':') {
                // printf("Break point\n");
                strcpy(stu[size], "\0");
                return 0;
            } else {
                if (scoretmp[0] == 'm') {
                    if (strcmp(scoretmp, "m:") == 0) return 0;
                    if (m) {
                        strcpy(stu[size], "\0");
                        math[size] = -1;
                        return 0;
                    } else {
                        ptr = &scoretmp[2];
                        math[size] = atoi(ptr);
                        m = 1;
                    }
                } else if (scoretmp[0] == 'e') {
                    if (strcmp(scoretmp, "e:") == 0) return 0;
                    if (e) {
                        strcpy(stu[size], "\0");
                        eng[size] = -1;
                        return 0;
                    } else {
                        ptr = &scoretmp[2];
                        eng[size] = atoi(ptr);
                        e = 1;
                    }
                } else if (scoretmp[0] == 'p') {
                    if (strcmp(scoretmp, "p:") == 0) return 0;
                    if (p) {
                        strcpy(stu[size], "\0");
                        prog[size] = -1;
                        return 0;
                    } else {
                        ptr = &scoretmp[2];
                        prog[size] = atoi(ptr);
                        p = 1;
                    }
                }
            }
        }
        ++size;
        return 1;
    }
}

bool print(char **ptrloc) {
    int i;
    char word[inputlength] = "\0";
    getword(ptrloc, word);
    if (strcmp(word, "\0") != 0) {
        return 0;
    } else {
        printf("name\tm\te\tp\n");
        for (i = 0; i < size; ++i) {
            printf("%s\t", stu[i]);
            if (math[i] == -1) printf("x\t");
            else printf("%d\t", math[i]);
            if (eng[i] == -1) printf("x\t");
            else printf("%d\t", eng[i]);
            if (prog[i] == -1) printf("x\n");
            else printf("%d\n", prog[i]);
        }
        return 1;
    }
}

bool query(char **ptrloc) {
    int i;
    char nametmp[inputlength];
    char target[namelength];
    ptrloc = getword(ptrloc, nametmp);
    do {
        if (nametmp[0] != 'n' || nametmp[1] != ':') {
            return 0;
        } else {
            if (strcmp(nametmp, "n:") == 0) return 0;
            char *ptr = &nametmp[2];
            char *qtr = target;
            while (*ptr) {
                *qtr++ = *ptr++;
            }
            *qtr = '\0';
            for (i = 0; i < size; ++i) {
                if (strcmp(stu[i], target) == 0) break;
            }
            if (i == size) {
                printf("Student %s not found.\n", target);
            } else {
                printf("%s\t", stu[i]);
                if (math[i] == -1) printf("x\t");
                else printf("%d\t", math[i]);
                if (eng[i] == -1) printf("x\t");
                else printf("%d\t", eng[i]);
                if (prog[i] == -1) printf("x\n");
                else printf("%d\n", prog[i]);
            }
        }
    } while (ptrloc = getword(ptrloc, nametmp));
    return 1;
}

bool delete(char **ptrloc) {
    int i, j;
    char nametmp[inputlength];
    char target[namelength];
    ptrloc = getword(ptrloc, nametmp);
    do {
        if (nametmp[0] != 'n' || nametmp[1] != ':') {
            return 0;
        } else {
            if (strcmp(nametmp, "n:") == 0) return 0;
            char *ptr = &nametmp[2];
            char *qtr = target;
            while (*ptr) {
                *qtr++ = *ptr++;
            }
            *qtr = '\0';
            for (i = 0; i < size; ++i) {
                if (strcmp(stu[i], target) == 0) break;
            }
            if (i == size) {
                printf("Student %s not found.\n", target);
            } else {
                for (j = i; j < size - 1; ++j) {
                    strcpy(stu[j], stu[j + 1]);
                    math[j] = math[j + 1];
                    eng[j] = eng[j + 1];
                    prog[j] = prog[j + 1];
                }
                strcpy(stu[j], "\0");
                math[j] = -1;
                eng[j] = -1;
                prog[j] = -1;
                --size;
            }
        }
    } while (ptrloc = getword(ptrloc, nametmp));
    return 1;
}

bool sort(char **ptrloc) {
    int i, j;
    char nametmp[namelength];
    int scoretmp;
    char word[inputlength] = "\0";
    getword(ptrloc, word);
    if (strcmp(word, "\0") != 0) {
        return 0;
    } else {
        for (i = size - 1; i > 0; --i) {
            for (j = 0; j < i; ++j) {
                if(strcmp(stu[j], stu[j + 1]) > 0) {
                    strcpy(nametmp, stu[j]);
                    strcpy(stu[j], stu[j + 1]);
                    strcpy(stu[j + 1], nametmp);
                    scoretmp = math[j];
                    math[j] = math[j + 1];
                    math[j + 1] = scoretmp;
                    scoretmp = eng[j];
                    eng[j] = eng[j + 1];
                    eng[j + 1] = scoretmp;
                    scoretmp = prog[j];
                    prog[j] = prog[j + 1];
                    prog[j + 1] = scoretmp;
                }
            }
        }
        return 1;
    }
}