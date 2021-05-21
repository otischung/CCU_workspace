#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/ioctl.h>

sig_atomic_t isExit = 0;
// main_jumpbuf;

int row = -1;
int col = -1;

void winChange(int signumber);
void sigShow(int signumber);
void sighandler(int signo);


//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    int sig_exist[100];
    int idx = 0;
    char input[1024];
    char *const lsargv[] = { "ls", "/", "-alhR", NULL};

    printf("本task的學號是 %d\n", getpid());
    for (idx = 0; idx < 100; idx++) {
        if (signal(idx, sigShow) == SIG_ERR) {
            sig_exist[idx] = 0;
        } else {
            sig_exist[idx] = 1;
        }
    }

    // 使用者按下ctrl-c，OS直接忽略ctrl-c，然後這個signal『『不會』』送給這個task
    // do {
    //     printf("告訴作業系統，使用者按下ctrl-c時，這個 「訊號（singal）」不處理\n");
    //     assert(signal(SIGINT, SIG_IGN)!=SIG_ERR);
    // }while(0);

    signal(SIGINT, sighandler);     // ctrl + c
    signal(SIGQUIT, sighandler);    // ctrl + backslash
    signal(SIGWINCH, winChange);    // change terminal's windows size
    signal(SIGTSTP, sighandler);    // ctrl + z

    printf("SIGKILL是直接殺掉一個task\n");
    if (signal(SIGKILL, sighandler) == SIG_ERR) {
        printf("無法改變SIGKILL的行為\n");
        perror("SIGKILL的問題，具體來說是");
    }
    
    if (signal(SIGSTOP, sighandler) == SIG_ERR) {
        printf("無法改變SIGSTOP的行為\n");
        perror("SIGSTOP的問題，具體來說是");
    }

    printf("**這個程式只能透過輸入 exit 或 EOF 結束**\n");

    // while (fgets(input, 1024, stdin) != NULL) {
    //     if (input[strlen(input) - 1] == '\n')
    //         input[strlen(input) - 1] =  '\0';
    //     if (!strcmp(input, "exit")) break;
    //     else continue;
    // }

    // 測試在fork的環境下是child是否繼承parent的signal的設定：no
    int child_pid = fork();
    if (child_pid == 0) {    //child
        printf("child：child準備執行execv('ls')，等一下試著按下ctr-c\n");
        printf("child：如果按下ctr-c無法終止，試著按下ctr-\\\n");
        printf("child：按下輸入鍵以後開始\n");
        char c = getchar();
        execvp(lsargv[0], lsargv);
    } else {    //parent
        printf("chld的pid是 %d\n", child_pid);
        signal(SIGCHLD, SIG_IGN);
        // 讓parent執行一個無窮迴圈
        while (fgets(input, 1024, stdin) != NULL) {
            if (input[strlen(input) - 1] == '\n')
                input[strlen(input) - 1] =  '\0';
            if (!strcmp(input, "exit")) break;
            else continue;
        }
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////


void winChange(int signumber) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    col = w.ws_col;
    row = w.ws_row;
    printf("row=%d, col=%d\n", row, col);
}

void sigShow(int signumber) {
    /****************************************************************************
     * According from the glibc 2.32 changelog:
     * The deprecated arrays sys_siglist, _sys_siglist, and sys_sigabbrev
       are no longer available to newly linked binaries, and their declarations
       have been removed from <string.h>.  They are exported solely as
       compatibility symbols to support old binaries.  All programs should use
       strsignal instead.
    *****************************************************************************/
    // printf("get a signal named '%d', '%s'\n", signumber,
    //        sys_siglist[signumber]);
    printf("Get a signal named '%d', '%s'\n", signumber, strsignal(signumber));
}


void sighandler(int signo) {
    if (signo == SIGINT) {
        printf(" 按下ctr-c，但殺不死我\n");
        // sleep(2);  //假裝在ctr-c裡面運算了10秒鐘
    }
    if (signo == SIGQUIT)
        printf(" 按下ctr-\\，但殺不死我\n");
    if (signo == SIGTSTP)
        printf(" 按下ctr-z，但殺不死我\n");
    // if (signo == SIGKILL)
    //     printf("\n按下ctr-z，但殺不死我\n");
}
