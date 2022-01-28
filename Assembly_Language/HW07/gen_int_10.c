#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;

    srand(time(NULL));
    fp = fopen("data.txt", "w+");
    for (int i = 0; i < 400; ++i) {
        for (int j = 0; j < 198; ++j) {
            fprintf(fp, "%d%c", rand() % 10, "\t\n"[j == 197]);
        }
    }
    fclose(fp);
}
