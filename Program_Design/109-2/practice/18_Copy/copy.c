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
    int ret;
    char *buf;

    if (argc != 3) usage(argv[0]);

    readfd = open(argv[1], O_RDONLY, S_IRUSR);
    if (readfd < 0) {
        perror("readfd open failed");
        exit(1);
    }

    fileSize = lseek(readfd, 0, SEEK_END);
    buf = (char *)malloc(fileSize * sizeof(char));
    lseek(readfd, 0, SEEK_SET);

    ret = read(readfd, buf, fileSize);

    writefd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (writefd < 0) {
        perror("writefd open failed");
        exit(1);
    }

    ret = write(writefd, buf, fileSize);

    return 0;
}
////////////////////////////////////////////////////////////////////////


void usage(char *progname) {
    fprintf(stderr, "format error.\nusage: %s <src> <dst>\n", progname);
    exit(1);
}
