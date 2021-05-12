#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool palidrome(char *key);

int main() {
    char input[1024];

    while (~scanf("%s", input)) {
        if (palidrome(input)) {
            printf("%s\n", input);
        }
    }
    return 0;
}

bool palidrome(char *key) {
    char *front, *end;
    front = key;
    end = key + strlen(key) - 1;

    while (front <= end) {
        if (*front == *end) {
            ++front;
            --end;
        } 
        else return false;
    }
    return true;
}
