#pragma once
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define forever while (1)

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static inline int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static inline int read_uint32_from_net(int fd, uint32_t *ret) {
    uint32_t n;
    *ret = 0;
    
    if (read(fd, (char *)&n, sizeof(n)) < 0) {
        return -1;
    }
    n = ntohl(n);
    *ret = n;
    return 0;
}

static sig_atomic_t broken_pipe_happened = 0;
static inline void broken_pipe_handler() { broken_pipe_happened = 1; }

static inline int write_uint32_to_net(int fd, uint32_t n) {
    n = htonl(n);
    broken_pipe_happened = 0;
    signal(SIGPIPE, broken_pipe_handler);
    int ret = write(fd, &n, sizeof(n));

    if (broken_pipe_happened) {
        leave_player(fd);
        return -1;
    }
    return ret;
}

static inline int read_n_and_string(int fd, char *buf, int max_n) {
    uint32_t n;
    if (read_uint32_from_net(fd, &n) < 0) {
        perror("read");
        return -1;
    }

    if (n > max_n - 1) {
        fprintf(stderr, "string too long\n");
        return -1;
    }
    if (read(fd, buf, n) < 0) {
        fprintf(stderr, "read failed\n");
        return -1;
    }
    buf[n] = '\0';
    return 0;
}
