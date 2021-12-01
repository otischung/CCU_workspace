#pragma once
#include <string.h>
const char username_passwords[][2][8192] = {
    {"asdf", "asdf"},
    {"qwerty", "qwerty"},
    {"123456", "123456"}
};

static inline int user_check(char *username, char *password) {
    for (int i = 0; i < 3; ++i) {
        if (!strcmp(username, username_passwords[i][0]) &&
            !strcmp(password, username_passwords[i][1]))
            return 0;
    }
    return 1;
}
