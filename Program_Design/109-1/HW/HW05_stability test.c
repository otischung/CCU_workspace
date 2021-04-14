#include <stdio.h>
#include <stdlib.h>
#define TEST_DATA_CNT 10

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubblesort(int* A, int* B, int length){
    int i, j, temp;
    for(i = length - 1; i > 0; --i){
        for(j = 0; j < i; ++j){
            if(A[j] > A[j + 1]){
                swap(&A[j], &A[j + 1]);
                swap(&B[j], &B[j + 1]);
            }
        }
    }
}

void selectionsort(int* A, int* B, int length){
    int i, j, temp, min;
    for(i = 0; i < length - 1; ++i){
        min = i;
        for(j = i + 1; j < length; ++j){
            if(A[min] > A[j]){
                min = j;
            }
        }
        swap(&A[i], &A[min]);
        swap(&B[i], &B[min]);
    }
}

void insertionsort(int* A, int* B, int length){
    int i, j, temp, key, _key;
    for (int i = 1; i < length; i++) {
        int key = A[i];
        int _key = B[i];
        int j = i - 1;
        while (key < A[j] && j >= 0) {
            A[j + 1] = A[j];
            B[j + 1] = B[j];
            --j;
        }
        A[j + 1] = key;
        B[j + 1] = _key;
    }
}

void shiftdown(int* A, int* B, int size, int index){
    int left = index * 2 + 1;
    int right = left + 1;
    int max = left;
    int temp;
    if(right == size){
        if(A[index] < A[left]){
            swap(&A[index], &A[left]);
            swap(&B[index], &B[left]);
        }
    }
    else if(right < size){
        if(A[left] < A[right])
            max = right;
        if(A[index] < A[max]){
            swap(&A[index], &A[max]);
            swap(&B[index], &B[max]);
            shiftdown(A, B, size, max);
        }
    }
}
 
void heapsort(int* A, int* B, int size){
    int i, temp;
    for(i = size - 1; i >= 0; --i)
        shiftdown(A, B, size, i);
    
    while(size > 1){
        swap(&A[0], &A[size - 1]);
        swap(&B[0], &B[size - 1]);
        --size;
        shiftdown(A, B, size, 0);
    }
}

int partition(int* A, int* B, int p, int r){
    int i = p + 1, j = r, temp;
    do{                             //No matter i is equal to j or not, you have to scan i and j through whole Aay at least once.
        while(A[i] <= A[p]){        //All of the elements from p+1 to i must less than pivot(p).
            if(i == r)              //If all of the elements except pivot(p) are less then p, then i must stop at the end of the Aay.
                break;
            else
                ++i;
        }
 
        while(A[j] >= A[p]){        //All of the elements from j to r must less than pivot(p).
            if(j == p)              //If all of the elements except pivot(p) are greater then p, then j must stop at the start of the Aay.
                break;
            else
                --j;
        }
        if(i < j){                   //If i >= j, then you have already done the partition.
            swap(&A[i], &A[j]);
            swap(&B[i], &B[j]);
        }
    } while(i < j);
    if(j != p){                     //Actually, when j==p, that is, swap the same item, it won't cause error.
        swap(&A[p], &A[j]);
        swap(&B[p], &B[j]);
    }
    return j;
}
 
void quicksort(int* A, int* B, int p, int r){
    if(p < r){
        int q = partition(A, B, p, r);
        quicksort(A, B, p, q - 1);
        quicksort(A, B, q + 1, r);
    }
}

int main(){
    int i, j;
    const int test_data[TEST_DATA_CNT] = { 3,5,3,1,2,5,4,1,2,4 };
    const int test_order[TEST_DATA_CNT] = { 0,1,2,3,4,5,6,7,8,9 };
    int execute_test_data[TEST_DATA_CNT] = { 3,5,3,1,2,5,4,1,2,4 };
    int execute_test_order[TEST_DATA_CNT] = { 0,1,2,3,4,5,6,7,8,9 };

    bubblesort(execute_test_data, execute_test_order, TEST_DATA_CNT);
    printf("The order after bubble sort:\n");
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_data[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_order[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        execute_test_data[i] = test_data[i];
        execute_test_order[i] = test_order[i];
    }

    selectionsort(execute_test_data, execute_test_order, TEST_DATA_CNT);
    printf("The order after selection sort:\n");
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_data[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_order[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        execute_test_data[i] = test_data[i];
        execute_test_order[i] = test_order[i];
    }

    insertionsort(execute_test_data, execute_test_order, TEST_DATA_CNT);
    printf("The order after insertion sort:\n");
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_data[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_order[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        execute_test_data[i] = test_data[i];
        execute_test_order[i] = test_order[i];
    }

    heapsort(execute_test_data, execute_test_order, TEST_DATA_CNT);
    printf("The order after heap sort:\n");
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_data[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_order[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        execute_test_data[i] = test_data[i];
        execute_test_order[i] = test_order[i];
    }

    quicksort(execute_test_data, execute_test_order, 0, TEST_DATA_CNT - 1);
    printf("The order after quick sort:\n");
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_data[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        printf("%d ", execute_test_order[i]);
    }
    putchar('\n');
    for(i = 0; i < TEST_DATA_CNT; ++i){
        execute_test_data[i] = test_data[i];
        execute_test_order[i] = test_order[i];
    }

    return 0;
}
/*

*/