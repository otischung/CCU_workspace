#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "client_impl.h"
#define forever while (1)

int main(int argc, char **argv) {
    int socket_fd;
    ssize_t n;
    char ip_addr[1024];
    char recvline[MAXLINE];
    struct sockaddr_in servaddr;
    int ret;

    printf("This is client\n");
    if (argc == 1) {
        strcpy(ip_addr, "127.0.0.1");
    } else if (argc == 2) {
        strcpy(ip_addr, argv[1]);
    } else {
        fprintf(stderr, "usage: %s, [IP address]\n", argv[0]);
        exit(1);
    }

    do {
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
        ret = login(socket_fd);
        if (ret < 0) {
            // close(socket_fd);
            fprintf(stderr, "login failed, trying to relogin\n\n");
        }
    } while (ret < 0);
    uint32_t player_id = 0;
    read_uint32_from_net(socket_fd, &player_id);
    printf("player ID: %u\n", player_id);
    impl(socket_fd, player_id);

    return 0;
}
