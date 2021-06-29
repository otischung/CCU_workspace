// #pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    // struct stat stbuf;
    off_t fileSize;
    char input[(1 << 14)];
    char buffer[8192];
    char *inptr, *bufptr;
    char **data;
    int fd;
    int ret, id;

    inptr = input;
    fd = open(argv[1], O_RDONLY, S_IRUSR);
    if (fd < 0) {
        perror("open file error");
        exit(1);
    }

    // fstat(fd, &stbuf);
    // fileSize = stbuf.st_size;
    fileSize = lseek(fd, 0, SEEK_END);
    ret = lseek(fd, 0, SEEK_SET);
    ret = read(fd, input, fileSize);

    data = (char **)malloc(1024 * sizeof(char *));

    while (*inptr) {
        id = 0;
        bufptr = buffer;
        memset(buffer, '\0', 8192);
        while (*inptr != '@' || *(inptr+1) != 'r' || *(inptr+2) != 'e' || *(inptr+3) != 'c' || *(inptr+4) != 'I' || *(inptr+5) != 'd' || *(inptr+6) != ':' || *(inptr+7) != ' ') {
            ++inptr;
        }
        inptr += 8;

        while (isdigit(*inptr)) {
            id = id * 10 + (*inptr - '0');
            ++inptr;
        }
        while (*inptr != '\n') {
            ++inptr;
        }
        ++inptr;
        while (*inptr && *inptr != '\n') {
            *bufptr++ = *inptr++;
        }
        *bufptr = '\0';
        data[id] = strdup(buffer);
        ++inptr;
    }

    printf("%s", data[9]);

    free(data);
    return 0;
}
