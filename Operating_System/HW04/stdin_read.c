#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
    char c;
    char *p = &c;

    asm volatile (
        "mov $0, %%rax\n"
        "mov $0, %%rdi\n"
        "mov %0, %%rsi\n"
        "mov $1, %%rdx\n"
        "syscall\n"
        : 
        : "m" (p)
        : "rax", "rdi", "rsi", "rdx"
    );

    printf("你輸入的字元是 '%c'\n", c);
    return 0;
}
