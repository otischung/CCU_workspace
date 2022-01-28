#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    int a, b;

    srand(time(NULL));
    fp = fopen("data.txt", "w+");
    for (int i = 0; i < 400; ++i) {
        for (int j = 0; j < 198; ++j) {
            a = rand() % 10 - 5;
            b = rand() % 10000;
            fprintf(fp, "%f%c", (float)a + (float)b / 10000.0, "\t\n"[j == 197]);
        }
    }
    fclose(fp);
}
