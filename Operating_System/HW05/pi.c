#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define ld long double
#define PI 3.14159265358979323846

ld *arr_upper;
ld *arr_lower;
// ld width = 0.5;  // 2^-1
ld width = 0.0009765625;  // 2^-10

typedef struct DATA {
    ld start;
    ld end;
    ld width;
    ld precision;
    int id;
} Data;

ld upper(ld x, ld width) {
    if (x > 1.0) return 0.0;
    ld height = sqrt(1 - x * x);
    return width * height;
}

ld lower(ld x, ld width) {
    return upper(x + width, width);
}

void thread(void *arg) {
    Data *data = (Data *)arg;
    ld i, upper_sum, lower_sum;

    // printf("thread %d created\n", data->id);
    upper_sum = 0.0, lower_sum = 0.0;
    for (i = data->start; i < data->end; i += width) {
        upper_sum += upper(i, width);
        lower_sum += lower(i, width);
    }
    arr_upper[data->id] = upper_sum * 4;
    arr_lower[data->id] = lower_sum * 4;
}

int main(int argc, char **argv) {
    int precision_digits = 10;
    int n_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);
    int temp = 0;
    ld precision, upper_sum, lower_sum, sum;
    ld start, step, remainder;
    int i, ret;
    pthread_t *id;
    Data *data;

    if (argc == 2) {
        if ((temp = atoi(argv[1])) != 0) {
            precision_digits = temp;
        }
    } else if (argc == 3) {
        if ((temp = atoi(argv[1])) != 0) {
            precision_digits = temp;
        }
        if ((temp = atoi(argv[2])) != 0) {
            n_threads = temp;
        }
    }

    arr_upper = (ld *)malloc(n_threads * sizeof(ld));
    arr_lower = (ld *)malloc(n_threads * sizeof(ld));
    precision = 1.0 / (pow(10, precision_digits + 1));
    data = (Data *)malloc(n_threads * sizeof(Data));
    id = (pthread_t *)malloc(n_threads * sizeof(pthread_t));
    step = (ld)(1.0 / (ld)n_threads);
    // printf("step = %Lf\n", step);
    do {
        start = 0.0;
        for (i = 0; i < n_threads - 1; ++i) {
            arr_upper[i] = 0.0;
            arr_lower[i] = 0.0;
            data[i].start = start;
            start += step;
            data[i].end = start;
            data[i].width = width;
            data[i].precision = precision;
            data[i].id = i;

            ret = pthread_create(&id[i], NULL, (void *)thread, (void *)&data[i]);
            if (ret != 0) {
                perror("pthread create error");
                exit(1);
            }
        }

        data[i].start = start;
        data[i].end = 1.0;
        data[i].width = width;
        data[i].precision = precision;
        data[i].id = i;

        ret = pthread_create(&id[i], NULL, (void *)thread, (void *)&data[i]);
        if (ret != 0) {
            perror("pthread create error");
            exit(1);
        }

        for (i = 0; i < n_threads; ++i) {
            pthread_join(id[i], NULL);
            // printf("THREAD %d JOIN\n", i);
        }

        upper_sum = 0;
        lower_sum = 0;
        for (i = 0; i < n_threads; ++i) {
            upper_sum += arr_upper[i];
            lower_sum += arr_lower[i];
        }
        // printf("-----upper sum = %.10Lf-----\n", upper_sum);
        // printf("-----lower sum = %.10Lf-----\n", lower_sum);
        width /= 2;
    } while (upper_sum - PI > precision || PI - lower_sum > precision);

    sum = (upper_sum + lower_sum) / 2;
    printf("pi = %.10Lf\n", sum);
    free(id);
    free(data);
    free(arr_lower);
    free(arr_upper);
    return 0;
}
/*
double fmod(double x, double y);
On success, these functions return the value x - n*y, for some integer n,
such that the returned value has the same sign as x and a magnitude less
than the magnitude of y.
*/
