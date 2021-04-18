#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
#define ARRSIZE 16777216  // 2 ^ 24

static void mergesort(int *, int);
static void heapsort(int *, int);
static void quicksort(int *, int);
static int cmp(const void *, const void *);
void swap(int *, int *);
static void merge_sort(int *, int, int);
static void merge(int *, int, int, int);
static void shiftdown(int *, int, int);
static int partition(int *, int, int);
static void quick_sort(int *, int, int);


////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    // setvbuf(stdout, NULL, _IOFBF, ARRSIZE);
    srand(time(NULL));
    char *method;
    int *arr;
    clock_t start, end;

    method = basename(argv[0]);
    arr = (int *)malloc(ARRSIZE * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }
    for (int i = 0; i < ARRSIZE; ++i) {
        arr[i] = rand();
    }

    start = clock();
    if (!strcmp(method, "mergesort")) {
        mergesort(arr, ARRSIZE);
    } else if (!strcmp(method, "heapsort")) {
        heapsort(arr, ARRSIZE);
    } else if (!strcmp(method, "quicksort")) {
        quicksort(arr, ARRSIZE);
    } else {
        method = "qsort";
        qsort(arr, ARRSIZE, sizeof(arr[0]), cmp);
    }
    end = clock();

    printf("%s used %ld microseconds.\n", method, end - start);
    printf("%s used %.2Lf seconds.\n", method, ((long double)(end - start)/1000000));
    // for (int i = 0; i < ARRSIZE; ++i) {
    //     printf("%d\n", arr[i]);
    // }

    free(arr);
    return 0;
}
////////////////////////////////////////////////////////////


static void mergesort(int *arr, int size) {  // call this
    merge_sort(arr, 0, size - 1);
}

static void heapsort(int *arr, int size) {  // call this
    for (int i = size; i >= 0; --i) {
        shiftdown(arr, i, size);
    }
    while (size > 1) {
        swap(&arr[0], &arr[size - 1]);
        shiftdown(arr, 0, --size);
    }
}

static void quicksort(int *arr, int size) {  // call this
    quick_sort(arr, 0, ARRSIZE - 1);
}

static int cmp(const void *_a, const void *_b) {
    int *a = (int *)_a;
    int *b = (int *)_b;
    return *a - *b;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void merge_sort(int *arr, int left, int right) {
    int mid = (left + right) / 2;
    if (left < right) {
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

static void merge(int *arr, int left, int mid, int right) {
    int leftlen = mid - left + 1;
    int rightlen = right - mid;
    int *leftarr = (int *)malloc(sizeof(int) * leftlen);
    int *rightarr = (int *)malloc(sizeof(int) * rightlen);
    int i, j, k;
    for (i = 0; i < leftlen; ++i) {
        leftarr[i] = arr[left + i];
        rightarr[i] = arr[mid + 1 + i];
    }

    i = 0; j = 0; k = left;
    while (i < leftlen && j < rightlen) {
        if (leftarr[i] <= rightarr[j]) {
            arr[k++] = leftarr[i++];
        } else {
            arr[k++] = rightarr[j++];
        }
    }
    while (i < leftlen) {
        arr[k++] = leftarr[i++];
    }
    while (j < rightlen) {
        arr[k++] = rightarr[j++];
    }

    free(leftarr);
    free(rightarr);
}

static void shiftdown(int *arr, int node, int size) {
    int left = node * 2 + 1;
    int right = node * 2 + 2;
    int max = left;

    if (right == size) {
        if (arr[left] > arr[node]) {
            swap(&arr[left], &arr[node]);
        }
    } else if (right < size) {
        if (arr[left] < arr[right]) {
            max = right;
        }
        if (arr[max] > arr[node]) {
            swap(&arr[max], &arr[node]);
        }
        shiftdown(arr, max, size);
    }
}

static int partition(int *arr, int pivot, int right) {
    int i = pivot + 1, j = right;

    do {                                // No matter i is equal to j or not, you have to scan i and j through whole Aay at least once.
        while(arr[i] <= arr[pivot]){        // All of the elements from pivot+1 to i must less than pivot(pivot).
            if(i == right)                  // If all of the elements except pivot(pivot) are less then pivot, then i must stop at the end of the Aay.
                break;
            else
                ++i;
        }
 
        while(arr[j] >= arr[pivot]){        // All of the elements from j to right must less than pivot(pivot).
            if(j == pivot)                  // If all of the elements except pivot(pivot) are greater then pivot, then j must stop at the start of the Aay.
                break;
            else
                --j;
        }
        if(i < j){                      // If i >= j, then you have already done the partition.
            swap(&arr[i], &arr[j]);
        }
    } while(i < j);

    if (j != pivot){                        // Actually, when j==pivot, that is, swap the same item, it won't cause error.
        swap(&arr[pivot], &arr[j]);
    }

    return j;
}

static void quick_sort(int *arr, int pivot, int right) {
    if(pivot < right){
        int q = partition(arr, pivot, right);
        quick_sort(arr, pivot, q - 1);
        quick_sort(arr, q + 1, right);
    }
}
