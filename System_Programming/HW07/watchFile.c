#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

int main(int argc, char **argv) {
    char *pathname = argv[1];
    char command[PATH_MAX] = "";
    struct stat buf;
    time_t time1, time2;

    if (stat(pathname, &buf) != 0) {
        perror(pathname);
        return 1;
    }

    time1 = buf.st_mtime;
    printf("Modified:\t%s\n", ctime(&time1));
    strcpy(command, "cat ");
    strncat(command, pathname, PATH_MAX - 1);
    system(command);
    putchar('\n');

    while (true) {
        stat(pathname, &buf);
        time2 = buf.st_mtime;
        if (time1 != time2) {
            printf("Modified:\t%s", ctime(&time2));
            printf("Last modified:\t%s\n", ctime(&time1));
            strcpy(command, "cat ");
            strncat(command, pathname, PATH_MAX - 1);
            system(command);
            putchar('\n');
            time1 = time2;
            command[0] = '\0';
        }
    }

    return 0;
}
