#pragma GCC optimize ("O3")
#pragma GCC diagnostic ignored "-Wunused"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

// -fsanitize=undefined -fsanitize=address

int main(int argc, char **argv) {
    int readfd, writefd;
    int ret;
    char *buf;
    struct stat stbuf;
    off_t fileSize;

    readfd = open(argv[1], O_RDONLY, S_IRUSR);
    if (readfd < 0) {
        perror("read file error");
        exit(1);
    }
    fstat(readfd, &stbuf);
    fileSize = stbuf.st_size;

    buf = (char *)malloc(2 * fileSize * sizeof(char));
    ret = read(readfd, buf, fileSize);

    // printf("%s", buf);

    writefd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (writefd < 0) {
        perror("read file2 error");
        exit(1);
    }
    write(writefd, buf, strlen(buf));

    free(buf);
    close(readfd);
    close(writefd);
    return 0;
}
