#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

unsigned long long count = 0;
void alarmHandler(int);

int main(int argc, char **argv) {
    short success;
    int nice_v;
    long cputhreads;  // The amount of threads of CPU
    pid_t childPid;
    cpu_set_t mask;  // The set of the CPU threads.

    if (argc != 2 && !isdigit(argv[1][0]) && argv[1][0] != '-' && argv[1][0] != '+') {
        fprintf(stderr, "format error\n");
        fprintf(stderr, "./nice_testing <int level>\n");
        return 1;
    }

    //    This block of code is to set CPU affinity to thread 0 only    //
    cputhreads = sysconf(_SC_NPROCESSORS_CONF);
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    // CPU_SET(1, &mask);
    success = sched_setaffinity(0, sizeof(mask), &mask);
    if (success != 0) {
        perror("setaffinity failed");
        return 1;
    }
    // Reference: https://blog.csdn.net/Z_Stand/article/details/107883684
    //////////////////////////////////////////////////////////////////////
    
    nice_v = atoi(argv[1]);
    childPid = fork();
    if (childPid == -1) {
        perror("fork error");
        return 1;
    }
    if (childPid > 0) {
        nice(nice_v);
        printf("Child: ");
    } else {
        printf("Parent: ");
    }

    signal(SIGALRM, alarmHandler);
    alarm(10);  // After 10 seconds, this process will be terminated

    while (true) ++count;

    return 0;
}

void alarmHandler(int signo) {
    printf("count = %llu\n", count);
    exit(0);
}
