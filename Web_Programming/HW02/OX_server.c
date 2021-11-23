#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAXLINE 8192

// O: 0, X: 1
short matrix[3][3];

#define cleanMatrix() ({              \
    for (int i = 0; i < 3; ++i) {     \
        for (int j = 0; j < 3; ++j) { \
            matrix[i][j] = -1;        \
        }                             \
    }                                 \
})

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

int main() {
    int listen_fd, connect_fd;
    FILE *connect_fp;
    struct sockaddr_in servaddr;  // <netinet/in.h>
    int ret;
    pid_t pid;
    unsigned val = 1;

    cleanMatrix();
    dumpMatrix(stdout);
    usage(stdout);
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);  // IPv4, TCP  <sys/socket.h>
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bzero(&servaddr, sizeof(servaddr));  // <strings.h>
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // <arpa/inet.h>
    servaddr.sin_port = htons(8000);
    ret = bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));  // <sys/socket.h>
    if (ret < 0) {
        perror("bind error");
        exit(1);
    }
    ret = listen(listen_fd, SOMAXCONN);  // <sys/socket.h>
    if (ret < 0) {
        perror("listen error");
        exit(1);
    }

    while (1) {
        connect_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);  // <sys/socket.h>
        if (connect_fd > 0) {
            fprintf(stderr, "connection accept\n");
        } else {
            perror("accept error");
            continue;
        }
        connect_fp = fdopen(connect_fd, "w+");

        /*---Close the socket---*/
        fclose(connect_fp);
        // shutdown(connect_fd, SHUT_RDWR);
        close(connect_fd);
    }
    return 0;
}
