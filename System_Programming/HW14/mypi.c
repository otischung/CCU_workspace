#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <stdatomic.h>

typedef struct DATA {
    struct drand48_data *rand_buffer;
    long thread_idx;
    long local_loopcnts;
} Data;

long cputhreads;    // How many threads can be created?
long threads;       // How many threads you want to create?.
long total_loopcnts;
// long *currentcnts;
// long *currenthits;
volatile long *currentcnts;
volatile long *currenthits;
struct timespec pre, cur;
bool firstSignal = true;
pthread_mutex_t mutex;

void thread(void *arg);
void sighandler(int signum);


//////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    long double pi;
    long totalcnts;
    long totalhits;
    long local_loopcnts, remainder;
    Data *data;
    struct drand48_data **rand_buffer;
    pthread_t *id;
    int ret;
    long i;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <loops> <threads>\n", argv[0]);
        exit(1);
    }
    
    total_loopcnts = atol(argv[1]);
    if (total_loopcnts < 1) {
        fprintf(stderr, "Too few loop counts.\n");
        exit(1);
    }
    
    cputhreads = sysconf(_SC_NPROCESSORS_CONF);
    threads = atol(argv[2]);
    printf("This machine can create at most %ld threads.\n", cputhreads);
    if (threads < 1) {
        fprintf(stderr, "Too few threads.\n");
        exit(1);
    } else if (threads > cputhreads) {
        printf("Warning: Too many threads allocated.\n");
    }

    signal(SIGINT, sighandler);
    signal(SIGHUP, SIG_IGN);

    // Create pthreads.
    totalcnts = 0;
    totalhits = 0;
    local_loopcnts = total_loopcnts / threads;
    remainder = total_loopcnts % threads;
    currentcnts = (long *)calloc(threads,  sizeof(long));
    currenthits = (long *)calloc(threads, sizeof(long));
    data = (Data *)malloc(threads * sizeof(Data));
    // rand_buffer = aligned_alloc(64, threads * sizeof(struct drand48_data *));
    rand_buffer = (struct drand48_data **)malloc(threads * sizeof(struct drand48_data *));
    id = (pthread_t *)malloc(threads * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));
    for (i = 0; i < threads - 1; ++i) {
        // rand_buffer[i] = aligned_alloc(64, sizeof(struct drand48_data));
        rand_buffer[i] = (struct drand48_data *)malloc(sizeof(struct drand48_data));
        // pthread_mutex_lock(&mutex);
        srand48_r(rand(), rand_buffer[i]);
        data[i].rand_buffer = rand_buffer[i];
        data[i].thread_idx = i;
        data[i].local_loopcnts = local_loopcnts;
        // printf(">data.thread_idx = %ld.\n", data.thread_idx);
        ret = pthread_create(&id[i], NULL, (void *)thread, (void *)&data[i]);
        if (ret != 0) {
            perror("pthread create error");
            // pthread_mutex_unlock(&mutex);
            exit(1);
        }
    }

    // rand_buffer[i] = aligned_alloc(64, sizeof(struct drand48_data));
    rand_buffer[i] = (struct drand48_data *)malloc(sizeof(struct drand48_data));
    // pthread_mutex_lock(&mutex);
    srand48_r(rand(), rand_buffer[i]);
    data[i].rand_buffer = rand_buffer[i];
    data[i].thread_idx = i;
    data[i].local_loopcnts = local_loopcnts + remainder;
    // printf(">data.thread_idx = %ld.\n", data.thread_idx);
    ret = pthread_create(&id[i], NULL, (void *)thread, (void *)&data[i]);
    if (ret != 0) {
        perror("pthread create error");
        // pthread_mutex_unlock(&mutex);
        exit(1);
    }
    

    for (i = 0; i < threads; ++i) {
        pthread_join(id[i], NULL);
    }

    for (i = 0; i < threads; ++i) {
        totalhits += currenthits[i];
        totalcnts += currentcnts[i];
    }

    pi = (long double)4 * ((long double)totalhits / (long double)totalcnts);
    printf("totalcnts = %ld\n", totalcnts);
    printf("totalhits = %ld\n", totalhits);
    printf("pi = %.8Lf\n", pi);

    for (i = 0; i < threads; ++i) {
        free(rand_buffer[i]);
    }
    free(data);
    free(rand_buffer);
    free(id);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////


void thread(void *arg) {
    Data *data;
    struct drand48_data *rand_buffer;
    long thread_idx;
    double point_x, point_y;
    long local_loopcnts;
    long local_cnts, local_hits;
    long refresh_counter, add_counter, remainder;
    double rand_d;
    
    data = (Data *)arg;
    rand_buffer = data->rand_buffer;
    thread_idx = data->thread_idx;
    local_loopcnts = data->local_loopcnts;
    local_cnts = 0;
    local_hits = 0;
    // pthread_mutex_unlock(&mutex);

    // printf(">>thread %ld created.\tLoopcnt = %ld.\n", thread_idx, local_loopcnts);
    if (local_loopcnts < 10000) refresh_counter = 1;
    else if (local_loopcnts >= 10000 && local_loopcnts < 10000000) refresh_counter = 1000;
    else refresh_counter = 100000;

    add_counter = local_loopcnts / refresh_counter;
    remainder = local_loopcnts % refresh_counter;

    for (long i = 0; i < refresh_counter; ++i) {
        for (long j = 0; j < add_counter; ++j) {  // This method will check local_loopcnts times.
            drand48_r(rand_buffer, &rand_d);
            point_x = rand_d;
            drand48_r(rand_buffer, &rand_d);
            point_y = rand_d;
            // ++currentcnts[thread_idx];
            ++local_cnts;
            if ((point_x * point_x + point_y * point_y) <= 1.0) {
                // ++currenthits[thread_idx];
                ++local_hits;
            }
        }
        currentcnts[thread_idx] = local_cnts;
        currenthits[thread_idx] = local_hits;
    }
    for (long i = 0; i < remainder; ++i) {
        drand48_r(rand_buffer, &rand_d);
        point_x = rand_d;
        drand48_r(rand_buffer, &rand_d);
        point_y = rand_d;
        // ++currentcnts[thread_idx];
        ++local_cnts;
        if ((point_x * point_x + point_y * point_y) <= 1.0) {
            // ++currenthits[thread_idx];
            ++local_hits;
        }
    }
    currentcnts[thread_idx] = local_cnts;
    currenthits[thread_idx] = local_hits;
    // printf(">thread %ld finish.\tlocalcnt = %ld.\n", thread_idx, local_cnts);
}

void sighandler(int signum) {
    long double pi;
    time_t diff;
    long totalcnts;
    long totalhits;
    long double progress;
    short bar;
    struct winsize w;

    totalcnts = 0;
    totalhits = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);

    /*        Calculate current pi        */
    for (long i = 0; i < threads; ++i) {
        totalhits += currenthits[i];
        totalcnts += currentcnts[i];
    }

    pi = (long double)4 * ((long double)totalhits / (long double)totalcnts);
    printf("\nCurrent pi = %.8Lf\n", pi);

    /*         Print progress bar         */
    progress = (long double)totalhits / (long double)total_loopcnts * 100;
    bar = (short)progress;
    printf("Processing: %.1Lf%%\n", progress);
    if (w.ws_col >= 100) {
        putchar('[');
        for (short i = 0; i < bar; ++i) {
            putchar('#');
        }
        for (short i = bar; i < 100; ++i) {
            putchar('.');
        }
        printf("]\n\n");
    } else if (50 <= w.ws_col && w.ws_col < 100) {
        putchar('[');
        for (short i = 0; i < bar / 2; ++i) {
            putchar('#');
        }
        for (short i = bar / 2; i < 50; ++i) {
            putchar('.');
        }
        printf("]\n\n");
    } else {
        printf("Your terminal size is too small, enlarge it too see progress bar.\n\n");
    }
    
    /*            Terminated?            */
    if (firstSignal) {
        clock_gettime(CLOCK_MONOTONIC, &pre);
    }
    clock_gettime(CLOCK_MONOTONIC, &cur);

    diff = cur.tv_sec - pre.tv_sec;
    if (!firstSignal && diff < 1) {
        printf("exit\n");
        _exit(signum);
    }

    firstSignal = false;
    pre = cur;
}
