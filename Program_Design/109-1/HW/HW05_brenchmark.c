#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define TEST_DATA_CNT 100000

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubblesort(int* A, int length){
    int i, j, temp;
    for(i = length - 1; i > 0; --i){
        for(j = 0; j < i; ++j){
            if(A[j] > A[j + 1]){
                swap(&A[j], &A[j + 1]);
            }
        }
    }
}

void selectionsort(int* A, int length){
    int i, j, temp, min;
    for(i = 0; i < length - 1; ++i){
        min = i;
        for(j = i + 1; j < length; ++j){
            if(A[min] > A[j]){
                min = j;
            }
        }
        swap(&A[i], &A[min]);
    }
}

void insertionsort(int* A, int length){
    int i, j, temp, key;
    for (int i = 1; i < length; i++) {
        int key = A[i];
        int j = i - 1;
        while (key < A[j] && j >= 0) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

void shiftdown(int* A, int size, int index){
    int left = index * 2 + 1;
    int right = left + 1;
    int max = left;
    int temp;
    if(right == size){
        if(A[index] < A[left]){
            swap(&A[index], &A[left]);
        }
    }
    else if(right < size){
        if(A[left] < A[right])
            max = right;
        if(A[index] < A[max]){
            swap(&A[index], &A[max]);
            shiftdown(A, size, max);
        }
    }
}
 
void heapsort(int* A, int size){
    int i, temp;
    for(i = size - 1; i >= 0; --i)
        shiftdown(A, size, i);
    
    while(size > 1){
        swap(&A[0], &A[size - 1]);
        --size;
        shiftdown(A, size, 0);
    }
}

int partition(int* A, int p, int r){
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
        }
    } while(i < j);
    if(j != p){                     //Actually, when j==p, that is, swap the same item, it won't cause error.
        swap(&A[p], &A[j]);
    }
    return j;
}
 
void quicksort(int* A, int p, int r){
    if(p < r){
        int q = partition(A, p, r);
        /*
        printf("%d -> %d: ", p, r);
        for (int i = p; i <= r; ++i){
            printf("%d ", A[i]);
        }
        printf("\n");
        */
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

int main(){
    int i;
    int test_data[TEST_DATA_CNT + 5];
    struct timeval start;
    struct timeval end;
    unsigned long diff;

    printf("There are %d numbers in array.\n", TEST_DATA_CNT);

    /********************************/
    /*      Create Random Data      */
    /********************************/

    srand(time(NULL));

    /*************************************************/
    /*      Test Performance for random number       */
    /*************************************************/
    printf("Test Performance for random number\n");

    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = rand();
    }

    gettimeofday(&start, NULL);
    bubblesort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of bubble sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = rand();
    }

    gettimeofday(&start, NULL);
    selectionsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of selection sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = rand();
    }

    gettimeofday(&start, NULL);
    insertionsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of insertion sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = rand();
    }

    gettimeofday(&start, NULL);
    heapsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of heap sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = rand();
    }

    gettimeofday(&start, NULL);
    quicksort(test_data, 0, TEST_DATA_CNT - 1);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of quick sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*************************************************/
    /*      Test Performance for reverse number       */
    /*************************************************/
    printf("Test Performance for reverse number\n");

    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = TEST_DATA_CNT - i;
    }

    gettimeofday(&start, NULL);
    bubblesort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of bubble sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);

    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = TEST_DATA_CNT - i;
    }

    gettimeofday(&start, NULL);
    selectionsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of selection sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = TEST_DATA_CNT - i;
    }

    gettimeofday(&start, NULL);
    insertionsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of insertion sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = TEST_DATA_CNT - i;
    }

    gettimeofday(&start, NULL);
    heapsort(test_data, TEST_DATA_CNT);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of heap sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    
    for(i = 0 ; i < TEST_DATA_CNT ; ++i){
        test_data[i] = TEST_DATA_CNT - i;
    }

    gettimeofday(&start, NULL);
    quicksort(test_data, 0, TEST_DATA_CNT - 1);
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;     // 實際的時間差
    printf("The performance of quick sort is %ld us (equal %f sec)\n", diff, diff / 1000000.0);
    return 0;
}

/*
Result:
When we don't call the swap function:
There are 100000 numbers in array.
Test Performance for random number
The performance of bubble sort is 25929031 us (equal 25.929031 sec)
The performance of selection sort is 27888448 us (equal 27.888448 sec)
The performance of insertion sort is 5019444 us (equal 5.019444 sec)
The performance of heap sort is 22908 us (equal 0.022908 sec)
The performance of quick sort is 12157 us (equal 0.012157 sec)
Test Performance for reverse number
The performance of bubble sort is 20200151 us (equal 20.200151 sec)
The performance of selection sort is 18724122 us (equal 18.724122 sec)
The performance of insertion sort is 10075395 us (equal 10.075395 sec)
The performance of heap sort is 13081 us (equal 0.013081 sec)
The performance of quick sort is 8426551 us (equal 8.426551 sec)

When we call the swap function:
There are 100000 numbers in array.
Test Performance for random number
The performance of bubble sort is 27501594 us (equal 27.501594 sec)
The performance of selection sort is 27697011 us (equal 27.697011 sec)
The performance of insertion sort is 4506096 us (equal 4.506096 sec)
The performance of heap sort is 18653 us (equal 0.018653 sec)
The performance of quick sort is 22244 us (equal 0.022244 sec)
Test Performance for reverse number
The performance of bubble sort is 18953562 us (equal 18.953562 sec)
The performance of selection sort is 18646857 us (equal 18.646857 sec)
The performance of insertion sort is 9337933 us (equal 9.337933 sec)
The performance of heap sort is 15140 us (equal 0.015140 sec)
The performance of quick sort is 8367527 us (equal 8.367527 sec)
*/