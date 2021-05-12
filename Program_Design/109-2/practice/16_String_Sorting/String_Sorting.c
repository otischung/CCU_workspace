#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *_a, const void *_b);


int main() {
    char buf[1024];
    char **strarr;
    
    strarr = (char **)malloc(32 * sizeof(char *));
    int wordCnt = 0;
    
    while(fgets(buf, 1024, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] =  '\0';
        }
        strarr[wordCnt++] = strdup(buf);
    }
    qsort(strarr, wordCnt, sizeof(strarr[0]), cmp);
    for (int i = 0; i < wordCnt; ++i) {
        printf("%s\n", strarr[i]);
    }
}


int cmp(const void *_a, const void *_b) {
    char **a = (char **)_a;
    char **b = (char **)_b;
    return strcmp(*a, *b);
}
