#include <stdlib.h>
#include <string.h>
// #define ARRSIZE 1024  // 2 ^ 10
#define ARRSIZE 16777216  // 2 ^ 24

#ifndef __sort_string
#define __sort_string
void mergesort(char **, int);
void heapsort(char **, int);
void quicksort(char **, int);
int cmp(const void *, const void *);
void swap(char **, char **);
void merge_sort(char **, int, int);
void merge(char **, int, int, int);
void shiftdown(char **, int, int);
int partition(char **, int, int);
void quick_sort(char **, int, int);

void mergesort(char **arr, int size) {  // call this
    merge_sort(arr, 0, size - 1);
}

void heapsort(char **arr, int size) {  // call this
    for (int i = size; i >= 0; --i) {
        shiftdown(arr, i, size);
    }
    while (size > 1) {
        swap(&arr[0], &arr[size - 1]);
        shiftdown(arr, 0, --size);
    }
}

void quicksort(char **arr, int size) {  // call this
    quick_sort(arr, 0, ARRSIZE - 1);
}

int cmp(const void *_a, const void *_b) {
    char **a = (char **)_a;
    char **b = (char **)_b;
    return strcmp(*a, *b);
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void merge_sort(char **arr, int left, int right) {
    int mid = (left + right) / 2;
    if (left < right) {
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(char **arr, int left, int mid, int right) {
    int leftlen = mid - left + 1;
    int rightlen = right - mid;
    int i, j, k;
    char **leftarr = (char **)malloc(sizeof(char *) * leftlen);
    for (i = 0; i < leftlen; ++i) {
        leftarr[i] = (char *)malloc(sizeof(char) * 128);
    }
    char **rightarr = (char **)malloc(sizeof(char *) * rightlen);
    for (i = 0; i < rightlen; ++i) {
        rightarr[i] = (char *)malloc(sizeof(char) * 128);
    }

    for (i = 0; i < leftlen; ++i) {
        strcpy(leftarr[i], arr[left + i]);
        strcpy(rightarr[i], arr[mid + 1 + i]);
    }

    i = 0; j = 0; k = left;
    while (i < leftlen && j < rightlen) {
        if ( strcmp(rightarr[j], leftarr[i]) ) {
            strcpy(arr[k++], leftarr[i++]);
        } else {
            strcpy(arr[k++], rightarr[j++]);
        }
    }
    while (i < leftlen) {
        strcpy(arr[k++], leftarr[i++]);
    }
    while (j < rightlen) {
        strcpy(arr[k++], rightarr[j++]);
    }

    for (i = 0; i < leftlen; ++i) {
        free(leftarr[i]);
    }
    for (i = 0; i < rightlen; ++i) {
        free(rightarr[i]);
    }
    free(leftarr);
    free(rightarr);
}

void shiftdown(char **arr, int node, int size) {
    int left = node * 2 + 1;
    int right = node * 2 + 2;
    int max = left;

    if (right == size) {
        if ( strcmp(arr[left], arr[node]) ) {
            swap(&arr[left], &arr[node]);
        }
    } else if (right < size) {
        if ( strcmp(arr[right], arr[left]) ) {
            max = right;
        }
        if ( strcmp(arr[max], arr[node]) ) {
            swap(&arr[max], &arr[node]);
        }
        shiftdown(arr, max, size);
    }
}

int partition(char **arr, int pivot, int right) {
    int i = pivot + 1, j = right;

    do {                                // No matter i is equal to j or not, you have to scan i and j through whole Aay at least once.
        while( strcmp(arr[pivot],  arr[i]) ){        // All of the elements from pivot+1 to i must less than pivot(pivot).
            if(i == right)                  // If all of the elements except pivot(pivot) are less then pivot, then i must stop at the end of the Aay.
                break;
            else
                ++i;
        }
 
        while( strcmp(arr[j], arr[pivot]) ){        // All of the elements from j to right must less than pivot(pivot).
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

void quick_sort(char **arr, int pivot, int right) {
    if(pivot < right){
        int q = partition(arr, pivot, right);
        quick_sort(arr, pivot, q - 1);
        quick_sort(arr, q + 1, right);
    }
}
#endif
