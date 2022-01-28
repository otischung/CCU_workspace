#include <assert.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int childPid;
    struct rusage resource = {0};

    childPid = fork();
    if (childPid > 0) {  //parent
        wait4(-1, NULL, 0, &resource);
        printf("voluntary context switches %ld\n", resource.ru_nvcsw);
        printf("involuntary context switches %ld\n", resource.ru_nivcsw);
        printf("soft page faults %ld\n", resource.ru_minflt);
        printf("hard page faults %ld\n", resource.ru_majflt);
        printf("stime %ld.%06ld\n", resource.ru_stime.tv_sec, resource.ru_stime.tv_usec);
        printf("utime %ld.%06ld\n", resource.ru_utime.tv_sec, resource.ru_utime.tv_usec);
    } else {
        execvp(argv[1], &argv[1]);
    }
}