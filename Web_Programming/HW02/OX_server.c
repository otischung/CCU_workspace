#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#include "serve_client.h"
#include "states.h"
#include "utils.h"
#define MAXLINE 8192
#define forever while (1)

/* ---------------- Define Matrix Operation ---------------- */
// O: 0, X: 1
short matrix[3][3];

#define cleanMatrix()                     \
    do {                                  \
        for (int i = 0; i < 3; ++i) {     \
            for (int j = 0; j < 3; ++j) { \
                matrix[i][j] = -1;        \
            }                             \
        }                                 \
    } while (0)

#define dumpMatrix(fp)                            \
    do {                                          \
        for (int i = 0; i < 3; ++i) {             \
            for (int j = 0; j < 3; ++j) {         \
                fputc(' ', (fp));                 \
                if (matrix[i][j] == 1) {          \
                    fputc('X', (fp));             \
                } else if (matrix[i][j] == 0) {   \
                    fputc('O', (fp));             \
                } else {                          \
                    fputc(' ', (fp));             \
                }                                 \
                fputc(' ', (fp));                 \
                if (j < 2)                        \
                    fputc('|', (fp));             \
            }                                     \
            if (i < 2)                            \
                fprintf((fp), "\n-----------\n"); \
        }                                         \
        fprintf((fp), "\n\n");                    \
    } while (0)

#define usage(fp)                                              \
    do {                                                       \
        fprintf((fp), "Enter two numbers for coordinate\n\n"); \
        fprintf((fp), " 0 0 | 0 1 | 0 2\n");                   \
        fprintf((fp), "----------------\n");                   \
        fprintf((fp), " 1 0 | 1 1 | 1 2\n");                   \
        fprintf((fp), "----------------\n");                   \
        fprintf((fp), " 2 0 | 2 1 | 2 2\n");                   \
    } while (0)

/* ---------------- Define Player's Information ---------------- */
typedef struct PLAYER {
    char name[MAXLINE];
    char pass[MAXLINE];
} Player;

void serve_login(int fd) {
    char username[MAXLINE];
    write(fd, "What is your name?\n", 20);
}

int main() {
    fd_set read_fds, active_fd_set;
    int sock_fd, new_fd, max_fd;
    struct sockaddr_in servaddr;  // <netinet/in.h>
    int ret, flags;
    unsigned val = 1;
    char command[MAXLINE];
    Player *player;

    printf("This is server\n");
    player = malloc(2 * sizeof(Player));
    strncpy(player[0].name, "asdf", MAXLINE);
    strncpy(player[0].pass, "asdf", MAXLINE);
    strncpy(player[1].name, "qwerty", MAXLINE);
    strncpy(player[1].pass, "qwerty", MAXLINE);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);  // IPv4, TCP  <sys/socket.h>
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bzero(&servaddr, sizeof(servaddr));  // <strings.h>
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // <arpa/inet.h>
    servaddr.sin_port = htons(8000);
    ret = bind(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));  // <sys/socket.h>
    if (ret < 0) {
        perror("bind error");
        exit(1);
    }
    ret = listen(sock_fd, SOMAXCONN);  // <sys/socket.h>
    if (ret < 0) {
        perror("listen error");
        exit(1);
    }
    FD_ZERO(&active_fd_set);
    FD_SET(sock_fd, &active_fd_set);
    max_fd = sock_fd;

    forever {
        read_fds = active_fd_set;
        ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (ret < 0) {
            perror("select error");
            continue;
        }
        for (int i = 0; i < FD_SETSIZE; ++i) {  // Service all sockets
            if (FD_ISSET(i, &read_fds)) {
                if (i == sock_fd) {  // Connection request on original socket
                    new_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);
                    if (new_fd < 0) {
                        perror("accept error");
                        continue;
                    }

                    FD_SET(new_fd, &active_fd_set);
                    if (new_fd > max_fd) {
                        max_fd = new_fd;
                    }
                    flags = fcntl(new_fd, F_GETFL, 0);
                    if (ret < 0) {
                        perror("fcntl read flags error");
                        close(new_fd);
                        continue;
                    }
                    ret = fcntl(new_fd, F_SETFL, flags | O_NONBLOCK);
                    if (ret == -1) {
                        perror("fcntl set nonblock error");
                        close(new_fd);
                        continue;
                    }
                } else {  // Data arriving on an already-connected socket
                    client_handle(i);
                }
            }
        }
    }

    /*---Close the socket---*/
    shutdown(new_fd, SHUT_RDWR);
    close(new_fd);
    close(sock_fd);
    return 0;
}
