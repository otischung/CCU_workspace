**Operating System Homework 03  資工3B 408410120 鍾博丞**

-----------------------------------------

## 環境配置

Operating System: Arch Linux 5.14.7-arch1-1 using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 451.3K IOPS, Random W: 325.6K IOPS)

## 修正程式碼

原本的程式碼如下

```c
#include <stdio.h>

int main(int argc, char **argv) {
    unsigned long msr;
    asm volatile (
        "rdtsc\n\t"				// Returns the time in EDX:EAX.
        "shl $32, %%rdx\n\t"    // Shift the upper bits left.
        "or %%rdx, %0"          // 'Or' in the lower bits.
        : "=m" (msr)            // msr會放在記憶體
        : 
        : "rdx"
    );
    printf("msr: %lx\n", msr);
}
```

修正為

```c
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
```

因為現在我們要直接放在記憶體，所以第 8 行我們將 or 的結果存在 rax 裡面，再把他搬回 msr 即可

---

最後的壓縮指令

`tar jcvf filename.tar.bz2 target`

