#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#define forever while (1)
#define MAXLINE 8192

int main(int argc, char **argv) {
    int socket_fd;
    FILE *socket_fp;
    ssize_t n;
    char ip_addr[1024];
    char recvline[MAXLINE];
    struct sockaddr_in servaddr;
    int ret;

    if (argc == 1) {
        strcpy(ip_addr, "127.0.0.1");
    } else if (argc == 2) {
        strcpy(ip_addr, argv[1]);
    } else {
        fprintf(stderr, "usage: %s, [IP address]\n", argv[0]);
        exit(1);
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    if (inet_pton(AF_INET, ip_addr, &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }
    if (connect(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
    if (ret == -1) {
        perror("fcntl set nonblock error");
        exit(1);
    }
    socket_fp = fdopen(socket_fd, "a+");
    setvbuf(socket_fp, NULL, _IOLBF, 4096);
    forever {
        fgets(recvline, MAXLINE, stdin);
        fprintf(socket_fp, "%s\n", recvline);
        while (fread(recvline, MAXLINE, 1, socket_fp) > 0) {
            printf("%s", recvline);
        }
    }

    fclose(socket_fp);
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return 0;
}
