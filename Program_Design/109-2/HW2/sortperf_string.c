#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
#include <sys/time.h>
// #define ARRSIZE 1024  // 2 ^ 10
#define ARRSIZE 16777216  // 2 ^ 24

static void mergesort(char **, int);
static void heapsort(char **, int);
static void quicksort(char **, int);
static int cmp(const void *, const void *);
void swap(char **, char **);
static void merge_sort(char **, int, int);
static void merge(char **, int, int, int);
static void shiftdown(char **, int, int);
static int partition(char **, int, int);
static void quick_sort(char **, int, int);


////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    // setvbuf(stdout, NULL, _IOFBF, ARRSIZE);
    srand(time(NULL));
    char *method;
    char **arr;
    char buf[128];
    struct timeval start, end;
    time_t diff;
    short mode; // 0: number, 1: A-Z, 2: a-z
    FILE *fp;
    int i;

    method = basename(argv[0]);
    arr = (char **)malloc(ARRSIZE * sizeof(char *));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = (char *)malloc(128 * sizeof(char));
        if (arr[i] == NULL) {
            perror("malloc failed");
            return 1;
        }
    }

    fp = fopen("./random_string.txt", "r");
    if (fp == NULL) {
        perror("Open file error");
        return 1;
    }

    i = 0;
    while (fgets(buf, 128, fp) != NULL) {
        if (i == ARRSIZE) break;
        strcpy(arr[i++], buf);
    }

    gettimeofday(&start, NULL);
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
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("%s used %ld microseconds.\n", method, diff);
    printf("%s used %.2lf microseconds.\n", method, (double)diff / 1000000.0);

    // for (int i = 0; i < ARRSIZE; ++i) {
    //     printf("%s", arr[i]);
    // }
    // putchar('\n');

    for (int i = 0; i < ARRSIZE; ++i) {
        free(arr[i]);
    }
    free(arr);
    fclose(fp);
    return 0;
}
////////////////////////////////////////////////////////////


static void mergesort(char **arr, int size) {  // call this
    merge_sort(arr, 0, size - 1);
}

static void heapsort(char **arr, int size) {  // call this
    for (int i = size; i >= 0; --i) {
        shiftdown(arr, i, size);
    }
    while (size > 1) {
        swap(&arr[0], &arr[size - 1]);
        shiftdown(arr, 0, --size);
    }
}

static void quicksort(char **arr, int size) {  // call this
    quick_sort(arr, 0, ARRSIZE - 1);
}

static int cmp(const void *_a, const void *_b) {
    char **a = (char **)_a;
    char **b = (char **)_b;
    return strcmp(*a, *b);
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

static void merge_sort(char **arr, int left, int right) {
    int mid = (left + right) / 2;
    if (left < right) {
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

static void merge(char **arr, int left, int mid, int right) {
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

static void shiftdown(char **arr, int node, int size) {
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

static int partition(char **arr, int pivot, int right) {
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

static void quick_sort(char **arr, int pivot, int right) {
    if(pivot < right){
        int q = partition(arr, pivot, right);
        quick_sort(arr, pivot, q - 1);
        quick_sort(arr, q + 1, right);
    }
}
