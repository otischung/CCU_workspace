#include <stdio.h>

int main() {
    int c;
    int cnt;

    cnt = 0;
    while ((c = getchar()) != EOF) {
        printf("%c", c);
        ++cnt;
        if (cnt % 10 == 0) printf("%c", 150);
    }
    putchar('\n');
    return 0;
}
