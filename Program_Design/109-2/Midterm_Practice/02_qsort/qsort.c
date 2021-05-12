#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *_a, const void *_b);


int main() {
    int arr[4096];
    int input;
    int size = 0;
    
    while(~scanf("%d", &input)) {
        arr[size++] = input;
    }
    qsort(arr, size, sizeof(arr[0]), cmp);
    for (int i = 0; i < size; ++i) {
        printf("%d\n", arr[i]);
    }
}


int cmp(const void *_a, const void *_b) {
    int *a = (int *)_a;
    int *b = (int *)_b;
    return *a - *b;
}
