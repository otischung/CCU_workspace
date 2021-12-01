#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include "states.h"
#include "utils.h"

static char buf[MAXLINE];
static short matrix[3][3];

#define cleanMatrix()                     \
    do {                                  \
        for (int i = 0; i < 3; ++i) {     \
            for (int j = 0; j < 3; ++j) { \
                matrix[i][j] = 0;         \
            }                             \
        }                                 \
    } while (0)

static void dump_matrix() {
    const char OX[] = " OX";
    puts("\033c");
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", OX[matrix[0][0]], OX[matrix[0][1]], OX[matrix[0][2]]);
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", OX[matrix[1][0]], OX[matrix[1][1]], OX[matrix[1][2]]);
    printf("+---+---+---+\n");
    printf("| %c | %c | %c |\n", OX[matrix[2][0]], OX[matrix[2][1]], OX[matrix[2][2]]);
    printf("+---+---+---+\n");
    puts("");
}

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

    login_state = OX_LOGIN_FAILED;
    read_uint32_from_net(socket_fd, &login_state);
    switch (login_state) {
        case OX_LOGIN_SUCCESS:
            printf("login success!\n");
            break;

        case OX_LOGIN_FAILED:
            printf("login failed!\n");
            return -1;
            break;

        default:
            printf("something went wrong!\n");
            printf("%u\n", login_state);
            return -1;
            break;
    }
    return 0;
}

// return: 0 for tie, 1 for win, 2 for lose, < 0 for errors
static int game_loop(int fd, int player_id) {
    cleanMatrix();
    dump_matrix();
    puts("waiting...");
    for (;;) {
        uint32_t action;
        read_uint32_from_net(fd, &action);
        switch (action) {
            case OX_ACT:
                uint32_t act_player;
                read_uint32_from_net(fd, &act_player);
                if (act_player == player_id) {
                    uint32_t x, y;
                    do {
                        dump_matrix();
                        printf("Your turn!\nPlease input 'x y' in [0, 2]\n");
                        scanf("%u %u", &x, &y);
                        printf("%u %u\n", x, y);
                    } while (!(x < 3 && y < 3) || (matrix[x][y] != 0));
                    uint32_t action_step = htonl(OX_ACT);
                    int x_bak = x, y_bak = y;
                    x = htonl(x);
                    y = htonl(y);
                    char *cur = buf;
                    memcpy(cur, &action_step, sizeof(action_step));
                    cur += sizeof(action_step);
                    memcpy(cur, &x, sizeof(x));
                    cur += sizeof(x);
                    memcpy(cur, &y, sizeof(y));
                    cur += sizeof(y);
                    write(fd, buf, cur - buf);
                    matrix[x_bak][y_bak] = 1;
                    dump_matrix();
                    printf("Waiting for other...\n");

                } else {
                    uint32_t x, y;
                    read_uint32_from_net(fd, &x);
                    read_uint32_from_net(fd, &y);
                    if (x > 3 || y > 3) {
                        printf("invalid game step. server bugged.\n");
                        printf("x: %u,  y: %u\n", x, y);
                        return -100;
                    }
                    matrix[x][y] = 2;
                    dump_matrix();
                }
                break;

            case OX_WIN:
                printf("win!\n");
                return 1;
                break;

            case OX_LOSE:
                printf("lose!\n");
                return 2;
                break;

            case OX_TIE:
                printf("tie!\n");
                return 0;
                break;

            default:
                break;
        }
    }
}
static int invite(int fd, uint32_t player_id) {
    char *cur = buf;
    player_id = htonl(player_id);
    uint32_t action_invite = htonl(OX_INVITE);
    memcpy(cur, &action_invite, sizeof(action_invite));
    cur += sizeof(action_invite);
    memcpy(cur, &player_id, sizeof(player_id));
    cur += sizeof(player_id);
    write(fd, buf, cur - buf);

    uint32_t ret;
    read_uint32_from_net(fd, &ret);
    return ret;
}

// return: 1: accept, 0: deny.
static int invite_request(int fd) {
    uint32_t invitor = 0;
    if (read_uint32_from_net(fd, &invitor) != 0) {
        perror("network error");
        exit(EXIT_FAILURE);
    }
    printf("[\033[33;1;5m*\033[0m] %u invites you for a new game! Do you accept it? (y/n)\n", invitor);
    char answer[8192];
    scanf("%8000s", answer);
    if (!strcmp(answer, "y")) {
        write_uint32_to_net(fd, OX_INVITE_ACCEPT);
        return 1;
    } else {
        write_uint32_to_net(fd, OX_INVITE_REJECT);
        return 0;
    }
}

static int impl(int fd, uint32_t player_id) {
RESTART:
    uint32_t n_clients = 0, action = 0;
    int max_fd;
    fd_set read_fds;
    int ret;
    while (1) {
        write_uint32_to_net(fd, OX_LIST_CLIENTS);
    PARSE_ACTION:
        if (read_uint32_from_net(fd, &action) != 0) {
            perror("network error");
            exit(EXIT_FAILURE);
        }
        switch (action) {
            case OX_LIST_CLIENTS:
                if (read_uint32_from_net(fd, &n_clients) != 0) {
                    perror("network error");
                    exit(EXIT_FAILURE);
                }
                if (n_clients == 0) {
                    printf("Nobody online now, waiting...\n");
                    sleep(3);
                } else {
                    printf("There %s %u players: \n", n_clients == 1 ? "is" : "are", n_clients);
                    for (int i = 0; i < n_clients; i++) {
                        uint32_t u = 0;
                        read_uint32_from_net(fd, &u);
                        printf(" %4u", u);
                    }
                    printf(
                        "\nEnter player ID to invite for a game, "
                        "or waiting for others inviting you:\n");

                    FD_ZERO(&read_fds);
                    FD_SET(STDIN_FILENO, &read_fds);
                    FD_SET(fd, &read_fds);
                    max_fd = max(STDIN_FILENO, fd);

                    forever {
                        ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
                        if (ret < 0) {
                            perror("select error");
                            continue;
                        }
                        for (int i = 0; i < max_fd + 1; ++i) {  // Service all sockets
                            if (FD_ISSET(i, &read_fds)) {
                                if (i == STDIN_FILENO) {  // Connection request on original socket
                                    uint32_t player_id;
                                    if (scanf("%u", &player_id) == EOF) {
                                        printf("bye\n");
                                        exit(0);
                                    }
                                    int result = invite(fd, player_id);
                                    if (!result) {
                                        printf("player %u is not online, or in another game already.\n",
                                               player_id);
                                        goto RESTART;
                                    } else {
                                        printf("Waiting for [%u]'s reply..\n", player_id);
                                        goto PARSE_ACTION;
                                    }
                                } else if (i == fd) {  // Data arriving on an already-connected socket
                                    goto PARSE_ACTION;
                                }
                            }
                        }
                    }
                }
                break;
            case OX_INVITE:
                if (invite_request(fd)) goto PARSE_ACTION;
                goto RESTART;
                break;
            case OX_START:
                game_loop(fd, player_id);
                goto RESTART;
                break;
            case OX_INVITE_REJECT:
                printf("[%u] declined your invitation!\n", player_id);
                goto RESTART;
                break;
            default:
                printf("unknown action_id: %u\n", action);
                break;
        }
    }

    return 0;
}
