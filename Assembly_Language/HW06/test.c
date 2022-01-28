#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[1024];
    sprintf(buf, "Hello %d\n", 1);

//     int arr[8] = {12, 4, 2, 45, 23, 8, 50, 67};
//     int arrsize = 8;
//     int i, j, temp;

//     i = arrsize - 1;
// LOOP1:
//     j = 0;
// LOOP2:
//     if (arr[j] > arr[j + 1]) {
//         temp = arr[j];
//         arr[j] = arr[j + 1];
//         arr[j + 1] = temp;
//     }
//     if (j < i) {
//         ++j;
//         goto LOOP2;
//     } else {
//         if (i > 0) {
//             --i;
//             goto LOOP1;
//         }
//     }

//     for (i = 0; i < 8; ++i) {
//         printf("%d ", arr[i]);
//     }
//     putchar('\n');
    return 0;
}
