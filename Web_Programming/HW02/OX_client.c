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

#include "states.h"
#include "utils.h"
#define forever while (1)
#define MAXLINE 8192

char buf[MAXLINE];

static int login(int socket_fd) {
    char username[1024];
    char password[1024];
    char *cur;
    uint32_t len_username;
    uint32_t len_password;
    uint32_t action_login;
    uint32_t login_state;

    printf("username: ");
    fgets(username, 1024, stdin);
    username[strlen(username) - 1] = '\0';
    printf("password: ");
    fgets(password, 1024, stdin);
    password[strlen(password) - 1] = '\0';

    action_login = htonl((uint32_t)OX_LOGIN);
    len_username = htonl((uint32_t)strlen(username));
    len_password = htonl((uint32_t)strlen(password));

    cur = buf;
    memcpy(cur, &action_login, sizeof(action_login));
    cur += sizeof(action_login);
    memcpy(cur, &len_username, sizeof(len_username));
    cur += sizeof(len_username);
    memcpy(cur, username, strlen(username));
    cur += strlen(username);
    memcpy(cur, &len_password, sizeof(len_username));
    cur += sizeof(len_password);
    memcpy(cur, password, strlen(password));
    cur += strlen(password);
    write(socket_fd, buf, cur - buf);

    // login_state = OX_LOGIN_FAILED;
    // read_uint32_from_net(socket_fd, &login_state);
    // switch (login_state) {
    //     case OX_LOGIN_SUCCESS:
    //         printf("login success!\n");
    //         break;

    //     case OX_LOGIN_FAILED:
    //         printf("login failed!\n");
    //         return -1;
    //         break;

    //     default:
    //         printf("something went wrong!\n");
    //         printf("%u\n", login_state);
    //         return -1;
    //         break;
    // }
    return 0;
}

int main(int argc, char **argv) {
    int socket_fd, max_fd;
    fd_set read_fds;
    ssize_t n;
    char ip_addr[1024];
    char recvline[MAXLINE];
    struct sockaddr_in servaddr;
    int ret, flags;

    printf("This is client\n");
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

    flags = fcntl(socket_fd, F_GETFL, 0);
    if (ret < 0) {
        perror("fcntl read flags error");
        close(socket_fd);
    }
    ret = fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
    if (ret == -1) {
        perror("fcntl set nonblock error");
        close(socket_fd);
    }

    do {
        ret = login(socket_fd);
        if (ret < 0) fprintf(stderr, "login failed, please relogin\n\n");
    } while (ret < 0);

    max_fd = max(STDIN_FILENO, socket_fd);
    forever {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(socket_fd, &read_fds);
        ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (ret < 0) {
            perror("select error");
            continue;
        }
        for (int i = 0; i < max_fd + 1; ++i) {  // Service all sockets
            if (FD_ISSET(i, &read_fds)) {
                if (i == STDIN_FILENO) {  // Connection request on original socket
                    fgets(recvline, MAXLINE, stdin);
                    write(socket_fd, recvline, strlen(recvline));
                } else if (i == socket_fd) {  // Data arriving on an already-connected socket
                    while (read(socket_fd, recvline, MAXLINE) > 0) {
                        printf("%s", recvline);
                    }
                }
            }
        }
    }

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return 0;
}
