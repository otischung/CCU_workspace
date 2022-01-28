#include <stdio.h>
#include <stdlib.h>

int quick_sort(int *array, int low, int high) {
    int pivot_point, pivot_item, i, j, temp;

    if (high <= low) {
        return 1;
    }

    pivot_item = array[low];
    j = low;

    for (i = low + 1; i <= high; i++) {
        if (array[i] >= pivot_item) {
            continue;
        }

        j++;

        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    pivot_point = j;

    temp = array[low];
    array[low] = array[pivot_point];
    array[pivot_point] = temp;

    quick_sort(array, low, pivot_point - 1);

    quick_sort(array, pivot_point + 1, high);

    return 1;
}

int main(int argc, char *argv[]) {
    int i = 0, k = 0;
    int a[argc - 1];

    for (k = 0; k < argc - 1; k++) {
        a[k] = atoi(argv[k + 1]);
    }

    quick_sort(a, 0, argc - 2);

    for (i = 0; i < argc - 1; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
