#define _GNU_SOURCE

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    //從inputFd將檔案寫到outputFd  File Descriptor
    ssize_t inputFd, outputFd;
    char *inputPtr, *outputPtr;

    //確定使用者輸入二個參數
    if (argc != 3) {
        char *filename = basename(argv[0]);
        printf("『%s』的功能是檔案複製，要有二個參數，來源檔案和目標檔案\n", filename);
        exit(0);
    }

    //打開來源檔案，只可讀取模式打開
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        char *filename = argv[1];
        char errmsg[4096];
        snprintf(errmsg, 4096, "無法開啟來源檔案 (%s)", filename);
        perror(errmsg);
        exit(1);
    }

    //打開目的檔案
    //注意 open 的參數，可讀、創造、歸零（O_WRONLY | O_CREAT | O_TRUNC）
    //比較常忘記的是歸零，是否歸零是情況而定
    //如果沒有歸零就會有新舊混淆的問題
    //資料庫系統（DBMS）打開打檔案通常不會歸零，因為他們會在既有的上面做更新
    //word打開檔案通常要歸零，因為使用者的新文章可能更短，這會造成新舊混淆問題
    //open後可對該檔案＊＊『可讀可寫 (O_RDWR) 』＊＊（因為mmap的需求），如果沒有該檔案，..
    //..就建立該檔案。如果要建立，設定該檔案的屬性為owner可讀可寫
    outputFd = open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (outputFd == -1) {
        char *filename = argv[2];
        char errmsg[4096];
        snprintf(errmsg, 4096, "無法打開目的檔案 (%s)", filename);
        perror(errmsg);
        exit(1);
    }

    //🍏 🍎 與 mycp 不同的地方
    off_t data_off = 0, hole_off = 0, cur_off = 0;
    off_t fileSize, blockSize, pos = 0;
    //🍏 🍎 拿到檔案大小的方法，用lseek移到檔案尾巴，看回傳值
    fileSize = lseek(inputFd, 0, SEEK_END);
    putchar('\n');
    printf("File size = %ld\t\tBytes\n", fileSize);
    printf("File size = %.4Lf\tKB\n", (long double)(fileSize / 1024));
    printf("File size = %.4Lf\t\tMB\n", (long double)(fileSize / 1024 / 1024));
    printf("File size = %.4Lf\t\tGB\n", (long double)(fileSize / 1024 / 1024 / 1024));
    //🍏 🍎 讀到大小後記得用lseek回到原位（0）
    lseek(inputFd, 0, SEEK_SET);

    //NULL，不指定映射到記憶體的哪個位置。通常不指定
    //filesize，將檔案中多少內容映射到記憶體
    //prot_read，只會對該段記憶體做讀取
    //MAP_SHARED，對mmap出的記憶體的所有修改讓整個系統裡的人都看到。因此底藏的檔案會跟著變更
    //inputFd從哪個檔案映射進來
    //0, 映射的起點為 0
    inputPtr = mmap(NULL, fileSize, PROT_READ, MAP_SHARED, inputFd, 0);
    putchar('\n');
    perror("mmap");
    printf("inputPtr = %p\n", inputPtr);

    //ftruncate的名字是：縮小, 實際上是設定檔案大小
    ftruncate(outputFd, fileSize);
    outputPtr = mmap(NULL, fileSize, PROT_WRITE, MAP_SHARED, outputFd, 0);
    perror("mmap, output");
    printf("outputPtr = %p\n", outputPtr);
    while (true) {
        //Set "inputFd" to the first place of data.
        cur_off = lseek(inputFd, cur_off, SEEK_DATA);
        data_off = cur_off;  // Assign
        //Set "outputFd" to the first place of hole.
        cur_off = lseek(inputFd, cur_off, SEEK_HOLE);
        hole_off = cur_off;
        //第一種情況，資料在前面，洞在後面，不用特別處理
        //第二種情況，洞在前面，資料在後面，處理一下
        if (data_off > hole_off) {
            //現在是這樣：
            //  ...............data data data data data....
            //  ^hole_off      ^data_off=cur_off
            //因為cur_off已經移到後面了，所以下一輪執行會變成
            //  ...............data data data data data....
            //                 ^data_off               ^hole_off=curoff
            continue;
        }
        //至此，data_off一定在前面，hole_off一定在後面
        blockSize = hole_off - data_off;
        lseek(inputFd, data_off, SEEK_SET);
        lseek(outputFd, data_off, SEEK_SET);

        memcpy(outputPtr + data_off, inputPtr + data_off, blockSize);
        
        lseek(inputFd, hole_off, SEEK_SET);
        lseek(outputFd, hole_off, SEEK_SET);
        
        if (lseek(outputFd, 0, SEEK_CUR) == fileSize)
            break;
    }
    close(inputFd);
    close(outputFd);

    return (EXIT_SUCCESS);
}
