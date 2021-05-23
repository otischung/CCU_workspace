#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MaxFileName 4096
#define MaxBufLen (1 << 18)
#define BlockSize 4096

void usage(char *progname) {
    fprintf(stderr, "%s <inputFile>\n", progname);
    fprintf(stderr, "Read data from inputFile, and output it to stdout.\n");
    exit(1);
}

int main(int argc, char **argv) {
    char inputFile[MaxFileName];
    char buf[MaxBufLen];
    int fd;
    int c;
    ssize_t readSize;
    off_t offset;

    if (argc != 2) usage(argv[0]);
    strcpy(inputFile, argv[1]);

    fd = open(inputFile, O_RDONLY, S_IRUSR);
    if (fd < 0) {
        fprintf(stderr, "Filename: %s, fd = %d\n", inputFile, fd);
        perror("open error");
        exit(1);
    }

    offset = 0;
    while ((readSize = read(fd, buf + offset, BlockSize)) > 0) {
        offset += readSize;
    }
    buf[offset] = '\0';
    write(1, buf, offset);

    close(fd);
    return 0;
}
