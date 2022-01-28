#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>

struct timespec ts = {0, 10};

//正在執行於哪一顆 core 上面
int cpu_p0, cpu_p1;

// 🐉 🐲 🌵 🎄 🌲 🌳 🌴 🌱 🌿 ☘️ 🍀
// Peteron's solution 所需要的變數
int turn = 0;
int flag1 = 0;
int flag0 = 0;
// 🐉 🐲 🌵 🎄 🌲 🌳 🌴 🌱 🌿 ☘️ 🍀

//統計現在正有多少個 thread 在 CS 中
int in_cs = 0;
//統計每一個thread進入 CS 的次數
int p1_in_cs = 0;
int p0_in_cs = 0;

//每秒鐘印出 P0 和 P1 進入 CS 的次數
void per_second(int signum) {
    printf("進入次數（每秒）p0: %5d, p1: %5d", p0_in_cs, p1_in_cs);
    printf("，分別執行於 core#%d 及 core#%d\n", cpu_p0, cpu_p1);
    p0_in_cs = 0;
    p1_in_cs = 0;
    alarm(1);
}

void p0(void) {
    printf("p0: start\n");
    while (1) {
        // 🐉 🐲 🌵 🎄 🌲 🌳 🌴 🌱 🌿 ☘️ 🍀
        // Peteron's solution 的進去部分的程式碼
        flag0 = 1;
        turn = 1;
        while (flag1 == 1 && turn == 1)
            ;  // waiting
        // 底下程式碼用於模擬在 critical section
        cpu_p0 = sched_getcpu();
        in_cs++;  // 計算有多少人在 CS 中
        // nanosleep(&ts, NULL);	// 睡 100 nanoseconds
        if (in_cs == 2) fprintf(stderr, "p0 及 p1都在 critical section\n");
        p0_in_cs++;  // P0在CS幾次
        // nanosleep(&ts, NULL);	// 睡 100 nanoseconds
        in_cs--;  // 計算有多少人在CS中
        // 🐉 🐲 🌵 🎄 🌲 🌳 🌴 🌱 🌿 ☘️ 🍀
        // Peteron's solution 的離開部分的程式碼
        flag0 = 0;
    }
}

void p1(void) {
    printf("p1: start\n");
    while (1) {
        flag1 = 1;
        turn = 0;
        while (flag0 == 1 && turn == 0)
            ;  // waiting
        // 底下程式碼用於模擬在 critical section
        cpu_p1 = sched_getcpu();
        in_cs++;
        // nanosleep(&ts, NULL);
        if (in_cs == 2) fprintf(stderr, "p0 及 p1都在 critical section\n");
        p1_in_cs++;
        // nanosleep(&ts, NULL);
        in_cs--;
        // 離開 critical section
        flag1 = 0;
    }
}

int main(void) {
    pthread_t id1, id2;
    alarm(1);
    signal(SIGALRM, per_second);
    pthread_create(&id1, NULL, (void *)p0, NULL);
    pthread_create(&id2, NULL, (void *)p1, NULL);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    return (0);
}
