#include <stdio.h>

int main() {
    int arr[8] = {12, 4, 2, 45, 23, 8, 50, 67};
    int arrsize = 8;
    int i, j, temp;

    // for (i = 7; i > 0; --i) {
    //     for (j = 0; j <= i - 1; ++j) {
    //         if (arr[j] > arr[j + 1]) {
    //             temp = arr[j];
    //             arr[j] = arr[j + 1];
    //             arr[j + 1] = temp;
    //         }
    //     }
    // }

    i = arrsize - 1;
LOOP1:
    j = 0;
LOOP2:
    if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
    }
    if (j < i) {
        ++j;
        goto LOOP2;
    } else {
        if (i > 0) {
            --i;
            goto LOOP1;
        }
    }


    for (i = 0; i < 8; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}
