/*
usage: ./NoZombie 10000
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <linux/sched.h>

struct task_struct *ts;

void manyChild(int num) {
    int i, pid, wstatus;
    for (int i = 0; i < num; ++i) {
        pid = vfork();
        if (pid == 0) {
            fprintf(stderr, "\rchild %d is created", i + 1);
            sleep(i + 1);
            exit(0);
        }
        if (pid != 0) wait(&wstatus);
    }
}

int main(int argc, char** argv) {
    int pid, num, wstatus;
    sscanf(argv[1], "%d", &num);
    pid = fork();
    if (pid == 0) {
        manyChild(num);
        exit(0);
    } else {
        wait(&wstatus);
    }
    getchar();
}
