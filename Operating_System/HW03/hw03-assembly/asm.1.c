#include <stdio.h>

int main(int argc, char **argv) {
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    __asm__ volatile (
        "movl $100, %%eax\n"    // eax = 100, mov'l' 代表 32 位元，mov 代表 64 位元
        "movl $200, %%ebx\n"    // ebx = 200
        "addl %%ebx, %%eax\n"   // eax += rbx
        "movl %%eax, %0\n"      // b = rax
        : "=g" (b)              // output, b 的代號是 "%0"，"=" 表示 write only，g 代表 gcc 幫我們挑選一個普通的暫存器 (例如：R0~R31)，m 代表可以放在記憶體
        : "g" (a), "g" (d)      // input, a 的代號是 "%1", b 的代號是 "%2"
        :"ebx", "eax"           // 提示 gcc 我們改變了 ebx 和 eax 的值，如果 gcc 需要這兩個暫存器的舊值，gcc 要自己想辦法保存並還原
    );
    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    return 0;
}
