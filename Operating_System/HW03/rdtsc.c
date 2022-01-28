#include <stdio.h>

int main(int argc, char **argv) {
    unsigned long msr;
    asm volatile(
        "rdtsc\n"             // Returns the time in EDX:EAX.
        "shl $32, %%rdx\n"    // Shift the upper bits left.
        "or %%rdx, %%rax\n"   // 'Or' in the lower bits.
        "mov %%rax, %0\n"
        : "=m" (msr)          // msr會放在記憶體
        : 
        : "rdx", "rax"
    );
    printf("msr: %lx\n", msr);
}
