#include <stdio.h>
#include <stdlib.h>

// int main() {
//     int a[8] = {2, 4, 8, 12, 23, 45, 50, 67};
//     int i = 0, size = 8;
//     printf("Input array: ");
// restart:
//     printf("%d\n", a[i]);
//     ++i;
//     --size;
//     if (size > 0)
//         goto restart;
//     printf("\n");
//     return 0;
// }

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    qsort(a, 10, sizeof(int), cmp);
    return 0;
}
