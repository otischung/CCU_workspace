#include <errno.h>
#include <stdio.h>
#include <unistd.h>

char* filepath;

void call_sys() {
    long ret;
    int mode = R_OK | W_OK;
    __asm__ volatile(
        "mov $21, %%rax\n"  // system call number "access"
        "mov %1, %%rdi\n"   // filename
        "mov %2, %%rsi\n"   // mode
        "syscall\n"
        "mov %%rax, %0"
        : "=m"(ret)
        : "g"(filepath), "g"(mode)
        : "rax", "rbx", "rcx", "rdx");
    printf("ret = %ld\n", ret);
    errno = ret * -1;
    printf("error code = %d\n", errno);
    perror("error");
}

// 執行時要給一個pathname，測試該pathname是否可以讀寫
int main(int argc, char** argv) {
    filepath = argv[1];
    printf("address of call_sys is %p\n", call_sys);
    getchar();
    call_sys();
}
