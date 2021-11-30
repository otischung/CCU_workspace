#pragma once
#include <stdint.h>

#include "states.h"
#include "utils.h"

static inline void login(int fd) {
}

static inline void list_client(int fd) {
}

static inline void invite(int fd) {
}

static inline void invite_result(int fd) {
}

static inline void act(int fd) {
}

static int client_handle(int fd) {
    uint32_t serve;
    if (read_uint32_from_net(fd, &serve) < 0) {
        return -1;
    }

    switch (serve) {
        case OX_LOGIN:
            login(fd);
            break;
        case OX_LIST_CLIENT:
            list_client(fd);
            break;
        case OX_INVITE:
            invite(fd);
            break;
        case OX_INVITE_RESULT:
            invite_result(fd);
            break;
        case OX_ACT:
            act(fd);
            break;
        default:
            return -1;
            break;
    }

    return 0;
}
