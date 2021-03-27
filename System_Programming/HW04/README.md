**System Programming Homework 04  資工2B 408410120 鍾博丞**

-----------------------------------------

### 環境配置

Operating System: Ubuntu 20.04 LTS using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

SSD: WD Black 256G WDS256G1X0C TLC (Seq. R: 2050MB/s, Seq. W: 700MB/s, Random R: 170K IOPS, Random W: 130K IOPS)

### 執行環境

執行`make`後，fileperf 會在 bin 資料夾裡，`cd` 進去就可以執行了

### 測試結果

#### <font color=#808080>strace 測量結果</font> 

\_IONBF

```bash
❯ time strace -c ./fileperf input.txt output.txt 0
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 62.08   33.184213           2  13699329           read
 37.87   20.243908           4   4957535           write
  0.04    0.023307           2      7947           rt_sigreturn
  0.00    0.000028           5         5           openat
  0.00    0.000005           5         1           writev
  0.00    0.000004           1         3           close
  0.00    0.000003           1         2           rt_sigaction
  0.00    0.000003           1         2           setitimer
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00   53.451471              18664851         2 total
strace -c ./fileperf input.txt output.txt 0
27.11s user
192.39s system
100% cpu
3:37.34 total
```

\_IOLBF 1KB

```bash
❯ time strace -c ./fileperf input.txt output.txt -1
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 99.06    1.356928           4    322901           write
  0.75    0.010237           3      3347           read
  0.14    0.001985         397         5           openat
  0.04    0.000556           2       222           rt_sigreturn
  0.00    0.000039          13         3           close
  0.00    0.000008           8         1           writev
  0.00    0.000007           1         4           fstat
  0.00    0.000004           2         2           setitimer
  0.00    0.000003           1         2           rt_sigaction
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    1.369767                326512         2 total
strace -c ./fileperf input.txt output.txt -1 
0.80s user
4.32s system
91% cpu
5.560 total
```

\_IOFBF 4KB

```bash
❯ time strace -c ./fileperf input.txt output.txt 4096
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 68.48    0.004913           1      3363           write
 31.25    0.002242           0      3347           read
  0.26    0.000019           1        17           rt_sigreturn
  0.00    0.000000           0         3           close
  0.00    0.000000           0         4           fstat
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1           writev
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         2           setitimer
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl 
  0.00    0.000000           0         5           openat
------ ----------- ----------- --------- --------- ----------------
100.00    0.007174                  6769         2 total
strace -c ./fileperf input.txt output.txt 4096
0.17s user
0.09s system
94% cpu
0.276 total
```
\_IOFBF 16KB

```bash
❯ time strace -c ./fileperf input.txt output.txt 16384
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 49.27    0.003034           0      3363           write
 28.66    0.001765         353         5           openat
 21.83    0.001344           0      3347           read
  0.13    0.000008           0        21           rt_sigreturn
  0.11    0.000007           1         4           fstat
  0.00    0.000000           0         3           close
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1           writev
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         2           setitimer
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.006158                  6773         2 total
strace -c ./fileperf input.txt output.txt 16384 
0.19s user
0.07s system
102% cpu
0.251 total
```

\_IOFBF 64KB

```bash
❯ time strace -c ./fileperf input.txt output.txt 65536
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 45.31    0.001759         351         5           openat
 37.76    0.001466           0      3363           write
 16.64    0.000646           0      3347           read
  0.15    0.000006           1         4           fstat
  0.13    0.000005           0        19           rt_sigreturn
  0.00    0.000000           0         3           close
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1           writev
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         2           setitimer
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.003882                  6771         2 total
strace -c ./fileperf input.txt output.txt 65536 
0.21s user
0.05s system
102% cpu
0.261 total
```

\_IOFBF 1MB

```bash
❯ time strace -c ./fileperf input.txt output.txt 1048576
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 56.59    0.003385           1      3363           write
 24.27    0.001452           0      3347           read
 17.80    0.001065         213         5           openat
  0.60    0.000036          12         3           close
  0.20    0.000012           3         4           fstat
  0.17    0.000010           0        21           rt_sigreturn
  0.15    0.000009           1         8           mmap
  0.12    0.000007           7         1           writev
  0.05    0.000003           1         2           rt_sigaction
  0.05    0.000003           1         2           setitimer
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.005982                  6774         2 total
strace -c ./fileperf input.txt output.txt 1048576 
0.20s user
0.06s system
102% cpu
0.260 total
```
\_IOFBF 8MB

```bash
❯ time strace -c ./fileperf input.txt output.txt 8388608
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 69.07    0.003826           1      3363           write
 30.62    0.001696           0      3347           read
  0.31    0.000017           0        22           rt_sigreturn
  0.00    0.000000           0         3           close
  0.00    0.000000           0         4           fstat
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1           writev
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         2           setitimer
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
  0.00    0.000000           0         5           openat
------ ----------- ----------- --------- --------- ----------------
100.00    0.005539                  6775         2 total
strace -c ./fileperf input.txt output.txt 8388608 
0.22s user
0.09s system
102% cpu
0.293 total
```

\_IOFBF 20MB (因為測試檔案為 14MB，故我自己多做了此測試)

```bash
❯ time strace -c ./fileperf input.txt output.txt 20971520
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 67.77    0.001539           0      3363           write
 30.21    0.000686           0      3347           read
  1.06    0.000024           4         5           openat
  0.44    0.000010           0        21           rt_sigreturn
  0.18    0.000004           4         1           writev
  0.13    0.000003           1         3           close
  0.13    0.000003           1         2           setitimer
  0.09    0.000002           1         2           rt_sigaction
  0.00    0.000000           0         4           fstat
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         6           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         1 arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.002271                  6774         2 total
strace -c ./fileperf input.txt output.txt 20971520 
0.22s user
0.05s system
101% cpu
0.268 total
```
-----------------------------------------

#### <font color=#808080>ltrace 測量結果</font> 

\_IONBF

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 0
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 22.57    0.000242         242         1 __cyg_profile_func_enter
 15.30    0.000164         164         1 __monstartup
 13.99    0.000150         150         1 __isoc99_fscanf
  7.18    0.000077          77         1 __cyg_profile_func_exit
  6.16    0.000066          66         1 fputs
  5.22    0.000056          56         1 fopen
  5.04    0.000054          54         1 fputc
  4.94    0.000053          53         1 atol
  4.57    0.000049          49         1 fgetc
  4.01    0.000043          43         1 calloc
  3.82    0.000041          41         1 setvbuf
  3.73    0.000040          40         1 strlen
  3.45    0.000037          37         1 __cxa_atexit
------ ----------- ----------- --------- --------------------
100.00    0.001072                    13 total
ltrace -c ./fileperf input.txt output.txt 0
36.32s user
178.80s system
100% cpu
3:33.02 total
```

\_IOLBF 1KB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt -1
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 20.85    0.000147         147         1 __monstartup
 10.78    0.000076          76         1 __isoc99_fscanf
  9.22    0.000065          65         1 __cyg_profile_func_exit
  8.79    0.000062          62         1 fputc
  7.38    0.000052          52         1 fputs
  7.23    0.000051          51         1 fopen
  5.67    0.000040          40         1 atol
  5.53    0.000039          39         1 __cyg_profile_func_enter
  5.25    0.000037          37         1 fgetc
  5.11    0.000036          36         1 __cxa_atexit
  4.96    0.000035          35         1 calloc
  4.68    0.000033          33         1 strlen
  4.54    0.000032          32         1 setvbuf
------ ----------- ----------- --------- --------------------
100.00    0.000705                    13 total
ltrace -c ./fileperf input.txt output.txt -1
1.04s user
3.70s system
119% cpu
3.947 total
```

\_IOFBF 4KB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 4096
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 23.17    0.000174         174         1 __monstartup
 10.25    0.000077          77         1 __cyg_profile_func_exit
  8.12    0.000061          61         1 fopen
  7.59    0.000057          57         1 __isoc99_fscanf
  7.19    0.000054          54         1 setvbuf
  5.86    0.000044          44         1 __cyg_profile_func_enter
  5.86    0.000044          44         1 calloc
  5.59    0.000042          42         1 __cxa_atexit
  5.46    0.000041          41         1 atol
  5.33    0.000040          40         1 fgetc
  5.19    0.000039          39         1 fputs
  5.19    0.000039          39         1 fputc
  5.19    0.000039          39         1 strlen
------ ----------- ----------- --------- --------------------
100.00    0.000751                    13 total
ltrace -c ./fileperf input.txt output.txt 4096
0.16s user
0.08s system
102% cpu
0.234 total
```

\_IOFBF 16KB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 16384
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 20.36    0.000149         149         1 __monstartup
  8.74    0.000064          64         1 __cyg_profile_func_exit
  8.47    0.000062          62         1 __isoc99_fscanf
  8.20    0.000060          60         1 calloc
  8.06    0.000059          59         1 setvbuf
  8.06    0.000059          59         1 fopen
  5.87    0.000043          43         1 __cxa_atexit
  5.60    0.000041          41         1 atol
  5.46    0.000040          40         1 __cyg_profile_func_enter
  5.33    0.000039          39         1 fputc
  5.33    0.000039          39         1 fgetc
  5.33    0.000039          39         1 strlen
  5.19    0.000038          38         1 fputs
------ ----------- ----------- --------- --------------------
100.00    0.000732                    13 total
ltrace -c ./fileperf input.txt output.txt 16384  0.18s user 0.07s system 102% cpu 0.246 total
```


\_IOFBF 64KB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 65536
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 20.52    0.000157         157         1 __monstartup
 13.20    0.000101         101         1 __isoc99_fscanf
  7.97    0.000061          61         1 calloc
  7.71    0.000059          59         1 fopen
  6.93    0.000053          53         1 setvbuf
  6.41    0.000049          49         1 __cyg_profile_func_exit
  5.75    0.000044          44         1 fgetc
  5.49    0.000042          42         1 __cxa_atexit
  5.36    0.000041          41         1 atol
  5.23    0.000040          40         1 fputs
  5.23    0.000040          40         1 __cyg_profile_func_enter
  5.23    0.000040          40         1 strlen
  4.97    0.000038          38         1 fputc
------ ----------- ----------- --------- --------------------
100.00    0.000765                    13 total
ltrace -c ./fileperf input.txt output.txt 65536
0.21s user
0.06s system
101% cpu
0.266 total
```


\_IOFBF 1MB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 1048576
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 19.44    0.000153         153         1 __monstartup
 10.29    0.000081          81         1 calloc
  9.66    0.000076          76         1 __cyg_profile_func_exit
  9.02    0.000071          71         1 setvbuf
  8.01    0.000063          63         1 __isoc99_fscanf
  7.37    0.000058          58         1 fopen
  5.34    0.000042          42         1 atol
  5.34    0.000042          42         1 __cyg_profile_func_enter
  5.34    0.000042          42         1 fgetc
  5.34    0.000042          42         1 __cxa_atexit
  4.96    0.000039          39         1 fputs
  4.96    0.000039          39         1 fputc
  4.96    0.000039          39         1 strlen
------ ----------- ----------- --------- --------------------
100.00    0.000787                    13 total
ltrace -c ./fileperf input.txt output.txt 1048576
0.17s user
0.09s system
97% cpu
0.262 total
```


\_IOFBF 8MB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 8388608
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 20.54    0.000152         152         1 __monstartup
 10.68    0.000079          79         1 __cyg_profile_func_exit
  8.11    0.000060          60         1 calloc
  7.84    0.000058          58         1 fopen
  7.57    0.000056          56         1 __isoc99_fscanf
  7.30    0.000054          54         1 setvbuf
  5.81    0.000043          43         1 __cxa_atexit
  5.68    0.000042          42         1 __cyg_profile_func_enter
  5.54    0.000041          41         1 atol
  5.27    0.000039          39         1 fputc
  5.27    0.000039          39         1 fgetc
  5.27    0.000039          39         1 strlen
  5.14    0.000038          38         1 fputs
------ ----------- ----------- --------- --------------------
100.00    0.000740                    13 total
ltrace -c ./fileperf input.txt output.txt 8388608
0.20s user
0.06s system
102% cpu
0.259 total
```


\_IOFBF 20MB

```bash
❯ time ltrace -c ./fileperf input.txt output.txt 20971520
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 17.81    0.000150         150         1 __monstartup
  9.14    0.000077          77         1 calloc
  8.67    0.000073          73         1 __cyg_profile_func_enter
  8.19    0.000069          69         1 __isoc99_fscanf
  7.96    0.000067          67         1 __cyg_profile_func_exit
  7.84    0.000066          66         1 __cxa_atexit
  7.60    0.000064          64         1 setvbuf
  7.48    0.000063          63         1 fopen
  5.34    0.000045          45         1 fgetc
  5.23    0.000044          44         1 atol
  5.11    0.000043          43         1 strlen
  4.87    0.000041          41         1 fputs
  4.75    0.000040          40         1 fputc
------ ----------- ----------- --------- --------------------
100.00    0.000842                    13 total
ltrace -c ./fileperf input.txt output.txt 20971520  0.20s user 0.08s system 102% cpu 0.278 total
```

### 結論

從上述測試結果來看，C API Library call 在不同的 buffer 設定裡被呼叫的次數皆相同，但是所花的時間大不相同，尤其從 IONBF 到 IOLBF 就有顯著差異了。這些我們可以從 C API Library call 呼叫了幾次 System call 來看，在 IONBF 之下，R/W 次數高達 1.8M 次，從 htop 可以得知單核心時常處於滿載狀態，而 iotop 顯示一直有 IO，但是磁碟使用率很低：相比之下，IOFBF 的 iotop 顯示在 buffer 滿的時候會有一次較為大幅的 IO，CPU 得以不用一直處理 system call，chipset 也不用一直處理零碎的磁碟 IO



當然，提高運作效率的代價就是佔用 RAM 空間，同時也會增加延遲，舉例，stdio 本身就是具有 IO buffer 的檔案指標，stderr 本身就是沒有 IO buffer，所以，平常的輸出結果到螢幕上，有一點延遲是可以接受的，但是如果是要製作進度條之類的東西，我們就是要看到當下的情況，不允許有延遲，一有改變就要立刻輸出，這時 stderr 的 IONBF 就派上用場了



------------------------------------------------------------------

最後的壓縮指令 
`tar jcvf filename.tar.bz2 target`