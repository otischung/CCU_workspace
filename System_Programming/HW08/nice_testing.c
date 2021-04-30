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
    int nice_v;
    pid_t childPid;
    cpu_set_t set;

    if (argc != 2 && !isdigit(argv[1][0]) && argv[1][0] != '-' && argv[1][0] != '+') {
        fprintf(stderr, "format error\n");
        fprintf(stderr, "./nice_testing <int level>\n");
        return 1;
    }

    CPU_ZERO(&set);
    CPU_SET(0, &set);
    
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
    alarm(1);

    while (true) ++count;

    return 0;
}

void alarmHandler(int signo) {
    printf("count = %llu\n", count);
    exit(0);
}
