#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXHEAP 0
#define MINHEAP 1

typedef struct HEAP {
    int *arr;
    int arrsize;
    int cnt;
} Heap;

void swap(int *a, int *b);
void heap_init(Heap *);
void heap_realloc(Heap *);
void heap_free(Heap *);
void heap_push(Heap *h, int key, bool type);
int heap_pop(Heap *h, bool type);
void heap_print(Heap *h);


///////////////////////////////////////////////////////////////////////////////
int main() {
    int input, mid, Lret, Rret;
    Heap Lheap, Rheap;
    bool first;

    heap_init(&Lheap);
    heap_init(&Rheap);
    first = true;

    setvbuf(stdout, NULL, _IOFBF, (1 << 14));
    
    while (~scanf("%d", &input)) {
        if (first) {
            heap_push(&Lheap, input, MAXHEAP);
            first = false;
            mid = input;
            printf("%d\n", mid);
            continue;
        }

        if (input <= mid) {
            heap_push(&Lheap, input, MAXHEAP);
            if (Lheap.cnt - Rheap.cnt > 1) {
                Lret = heap_pop(&Lheap, MAXHEAP);
                heap_push(&Rheap, Lret, MINHEAP);
                // heap_push(&Rheap, heap_pop(&Lheap, MAXHEAP), MINHEAP);
            }
        } else {
            heap_push(&Rheap, input, MINHEAP);
            if (Rheap.cnt > Lheap.cnt) {
                Rret = heap_pop(&Rheap, MINHEAP);
                heap_push(&Lheap, Rret, MAXHEAP);
                // heap_push(&Lheap, heap_pop(&Rheap, MINHEAP), MAXHEAP);
            }
        }

        if ((Lheap.cnt + Rheap.cnt) % 2) {  // odd
            mid = Lheap.arr[0];
        } else {  // even
            mid = (Lheap.arr[0] + Rheap.arr[0]) / 2;
        }
        printf("%d\n", mid);
    }

    heap_free(&Lheap);
    heap_free(&Rheap);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_init(Heap *h) {
    h->arr = (int *)calloc((1 << 14), sizeof(int));
    h->arrsize = (1 << 14);
    h->cnt = 0;
}

void heap_realloc(Heap *h) {
    h->arrsize <<= 1;
    h->arr = (int *)realloc(h->arr, h->arrsize * sizeof(int));
}

void heap_free(Heap *h) {
    free(h->arr);
}

void heap_push(Heap *h, int key, bool type) {
    int parent, child;
    
    if (h->arrsize == h->cnt) {
        heap_realloc(h);
    }
    h->arr[h->cnt] = key;

    // maintain heap //
    child = h->cnt;
    parent = (h->cnt - 1) / 2;
    while (child > 0) {
        if (type == MAXHEAP) {
            if (h->arr[parent] < h->arr[child]) {
                swap(&h->arr[parent], &h->arr[child]);
            }
        } else {  // MINHEAP
            if (h->arr[parent] > h->arr[child]) {
                swap(&h->arr[parent], &h->arr[child]);
            }
        }
        child = parent;
        parent = (parent - 1) / 2;
    }
    ++(h->cnt);
}

int heap_pop(Heap *h, bool type) {
    int traverse, left, right, comp;

    swap(&h->arr[0], &h->arr[--(h->cnt)]);
    traverse = 0;
    while (1) { // traverse < h->cnt
        if (type == MAXHEAP) {
            if (traverse * 2 + 2 == h->cnt) {
                left = traverse * 2 + 1;
                if (h->arr[traverse] < h->arr[left]) {
                    swap(&h->arr[traverse], &h->arr[left]);
                }
                break;
            } else if (traverse * 2 + 2 < h->cnt) {
                left = traverse * 2 + 1;
                right = traverse * 2 + 2;
                comp = left;
                if (h->arr[left] < h->arr[right]) {
                    comp = right;
                }
                if (h->arr[traverse] < h->arr[comp]) {
                    swap(&h->arr[traverse], &h->arr[comp]);
                    traverse = comp;  // iterative step
                } else break;
            } else break;
        } else { // MINHEAP
            if (traverse * 2 + 2 == h->cnt) {
                left = traverse * 2 + 1;
                if (h->arr[traverse] > h->arr[left]) {
                    swap(&h->arr[traverse], &h->arr[left]);
                }
                break;
            } else if (traverse * 2 + 2 < h->cnt) {
                left = traverse * 2 + 1;
                right = traverse * 2 + 2;
                comp = left;
                if (h->arr[left] > h->arr[right]) {
                    comp = right;
                }
                if (h->arr[traverse] > h->arr[comp]) {
                    swap(&h->arr[traverse], &h->arr[comp]);
                    traverse = comp;  // iterative step
                } else break;
            } else break;
        }
    }

    return h->arr[h->cnt];
}

void heap_print(Heap *h) {
    printf("arrsize = %d\n", h->arrsize);
    printf("cnt = %d\n", h->cnt);
    for (int i = 0; i < h->cnt; ++i) {
        printf("%d%c", h->arr[i], " \n"[i == h->cnt - 1]);
    }
}
