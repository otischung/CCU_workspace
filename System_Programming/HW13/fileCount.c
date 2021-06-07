#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pipefd[2];
    int ret, wstat, pid1, pid2;
    char dirName[4096] = "";
    char *const lsargv[] = { "ls", "-R", dirName, NULL };
    char *const wcargv[] = { "wc", "-l", NULL };

    if (argc != 2) {
        fprintf(stderr, "format error.\nusage: %s <dir>\n", argv[0]);
        exit(1);
    }
    
    
    if (argv[1][0] == '.' && argv[1][1] == '/');
    else if (argv[1][0] != '/') strcpy(dirName, "/");
    strncat(dirName, argv[1], 4094);

    pipe(pipefd);
    printf("parent's pid = %d\n", getpid());
    printf("the process group leader is %d\n", getpgrp());
    pid1 = fork();   //產生第一個child
    if (pid1 == 0) {
        close(1);   //關閉stdout
        dup(pipefd[1]); //將pipefd[1]複製到stdout
        close(pipefd[0]);   //將沒用到的關閉
        close(pipefd[1]);   //將沒用到的關閉
        ret = execvp(lsargv[0], lsargv);   //執行ls，ls會將東西藉由stdout輸出到pipefd[1]
        if (ret == -1) perror("ls error");
    } else printf("1st child's pid = %d: ls\n", pid1);

    if (pid1 > 0) {    
        pid2 = fork();//產生第二個child
        if (pid2 == 0) {
            close(0);   //關閉stdin
            dup(pipefd[0]); //將pipefd[0]複製到stdin
            close(pipefd[0]);   //將沒用到的關閉
            close(pipefd[1]);   //將沒用到的關閉
            execvp(wcargv[0], wcargv);   //執行wc，wc將透過stdin從pipefd[0]讀入資料
        } else printf("2nd child's pid = %d: wc\n", pid2);
    }

    //parent一定要記得關掉pipe不然wc不會結束（因為沒有接到EOF）
    close(pipefd[0]); close(pipefd[1]);
    printf("child %d terminated.\n", wait(&wstat));
    printf("child %d terminated.\n", wait(&wstat));

    return 0;
}
