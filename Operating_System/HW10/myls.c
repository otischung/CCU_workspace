#include <unistd.h>

int main() {
    char *const lsargv[] = {"/usr/bin/ls", "-lash", NULL};
    execvp(lsargv[0], lsargv);
}
