#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void usage(char *progname);


////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    off_t fileSize;
    int readfd, writefd;
    ssize_t ret;
    char *buf, *ptr;

    if (argc != 2) usage(argv[0]);

    readfd = open(argv[1], O_RDONLY, S_IRUSR);
    if (readfd < 0) {
        perror("readfd open failed");
        exit(1);
    }

    fileSize = lseek(readfd, 0, SEEK_END);
    buf = (char *)malloc(fileSize * sizeof(char));
    lseek(readfd, 0, SEEK_SET);

    ret = read(readfd, buf, fileSize);
    buf[fileSize] = '\0';

    // printf("%s", buf);

    ptr = buf;
    while (*ptr) {
        if (*ptr >= 'A' && *ptr <= 'Z') {
            *ptr += 32;
        }
        ++ptr;
    }

    // printf("%s", buf);

    writefd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
    if (writefd < 0) {
        perror("writefd open failed");
        exit(1);
    }
    ret = write(writefd, buf, fileSize);

    free(buf);
    return 0;
}
////////////////////////////////////////////////////////////////////////


void usage(char *progname) {
    fprintf(stderr, "format error.\nusage: %s <file>\n", progname);
    exit(1);
}