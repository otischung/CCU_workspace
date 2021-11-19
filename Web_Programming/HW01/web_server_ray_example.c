#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/sendfile.h>
#include <sys/wait.h>

int main() {
    int fd;
    unsigned val = 1;
    struct sockaddr_in sin;
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    int wstatus;

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9000);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct sockaddr*) &sin, sizeof(sin)) < 0) { 
        perror("bind"); 
        exit(-1);
    }
    if (listen(fd, SOMAXCONN) < 0) { 
        perror("listen");
        exit(-1); 
    }
    struct sockaddr_in psin;
    signal(SIGCHLD, SIG_IGN); // prevent child zombie
    while (1) {
        socklen_t s = sizeof(psin);
        int p_fd = accept(fd, (struct sockaddr*) NULL, NULL);
        fprintf(stderr, "accept!\n");
        if (p_fd < 0) {
            perror("accept");
            continue;
        }
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            sleep(3);
            char header[] =  
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: image/jpeg\r\n"
                "\r\n"
                ;
            write(p_fd, header, sizeof(header) - 1);

            int img_fd = open("./test.jpg", O_RDONLY);
            char buf[8192];
            for (int s = 0; (s = read(img_fd, buf, 1024)) > 0; ) {
                write(p_fd, buf, s);
            }
            shutdown(p_fd, SHUT_RDWR);
            close(p_fd);
            close(img_fd);
            exit(0);
        }
        close(p_fd);
    }
}

/*
2021.10.21 Ray asked:
教授，想請問 fork 之後要 close 掉 accept 出來的 connfd 嗎？
因為我寫的如果 fork 完之後 parent 先執行了 close，瀏覽器的 console 會收到 connection reset
但是投影片是這麼寫的。

2021.10.23 Prof. answered:
我猜測可能的原因是你在 HTTP response header 裡面並未指定 Content-length，使得瀏覽器沒有辦法
確切知道圖片什麼時候傳完。
因此當你把 p_fd close 掉時，如果瀏覽器有再發送任何內容，就會引發 reset。

另一種可能是你並未在處理完 HTTP request 後才開始回傳圖片，因此也有可能在圖片很快傳完後
(如果圖片 size 不大)，就立即執行 close(p_fd)，但這時 request 才到 server，也會引發 reset。

一個 reset 會發生時機都是封包傳到一個已經被 close 的 socket，所以可以朝這個方向去 debug。
請先試試看是否為這兩種情況之一，謝謝。
*/
