// xxd -b test.txt
// xxd test.txt
#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        printf("%d ", c);
    }
    putchar('\n');
    return 0;
}
