#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char** argv) {
    int c;
    FILE* newin, *newout, *newerr;
    int fdin, fdout, fderr;
    // 底下這一行是將『標準輸入』改成從 "/dev/null"
    // dev/null : 在類Unix系統中，/dev/null，或稱空設備，是一個特殊的設備文件，它丟棄一切寫入其中的數據（但報告寫入操作成功），
    // 🟧 🟨 🟩 🟦讀取它則會立即得到一個EOF。🟧 🟨 🟩 🟦
    // 原文網址：https://kknews.cc/code/valkama.html
    newin = freopen("/dev/null", "R+", stdin);          // 1️⃣ newin = 0x0
    // 底下這一行是將『標準輸出』改成從 "stdout.log"
    newout = freopen("./stdout.log", "w+", stdout);     // 2️⃣ 
    // 底下這一行是將『標準錯誤』改成從 "stderr.log"
    newerr = freopen("./stderr.log", "w+", stderr);     // 3️⃣

    // fdin = fileno(newin);  // Can't use because of /dev/null
    fdout = fileno(newout);
    fderr = fileno(newerr);

    setvbuf(newout, NULL, _IOLBF, 1024);
    setvbuf(newerr, NULL, _IONBF, 0);

    // 假裝我們的程式需要印出一些東西，然後又讀取一些東西
    for (int i = 0; i < 10; ++i) {
        printf("%d: hello\n", i);                       // 4️⃣
        // fprintf(newout, "%d: hello\n", i);
        // sync();          // useless
        // fsync(fdout);    // useless
        // fflush(newout);
        c = getchar();                                  // 5️⃣ 
    }
    // 睡10秒鐘
    // 告訴作業系統，忽略『掛斷』的信號。SIGHUP。signal hang up
    signal(SIGHUP, SIG_IGN);                            // 6️⃣
    // 在10秒內切斷terminal的連線會怎樣呢？ls還會正常執行嗎？
    printf("試著在10秒內切斷連線\n");
    // fprintf(newout, "試著在10秒內切斷連線\n");
    for (int i = 0; i < 10; ++i) {
        fprintf(stderr, "*");
        // fprintf(newerr, "*");
        sleep(1);
        // sync();          // useless
    }
    fprintf(stderr, "\n");
    execlp("ls", "ls", "/", "-R", NULL);                // 7️⃣
}
