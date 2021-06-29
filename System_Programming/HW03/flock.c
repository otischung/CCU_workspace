#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>

#define BUF_SIZE 8

void usage();

int main(int argc, char* argv[]) {
	int flockFd;
	int ret;  // check flock success (0) or not (-1)
    char buffer[BUF_SIZE];
    int offset;
	char opt;

	memset(buffer, 0, sizeof(char) * BUF_SIZE);

	if (argc != 1 && argc != 2) {
		usage();
		exit(1);
	}

	flockFd = open("./flock.db", O_RDWR, S_IRUSR | S_IWUSR);
	if (flockFd == -1) {  // The file doesn't exist.
		flockFd = open("./flock.db", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		strcpy(buffer, "3500");
		write(flockFd, buffer, strlen(buffer));
	}
	printf("flockFd = %d is opened\n", flockFd);
	
	if (argc == 2) sscanf(argv[1], "%c", &opt);  // string to char
	
	for (int i = 1; i <= 1000; ++i) {
		if (argc == 1) {
			ret = flock(flockFd, LOCK_EX);
		} else {
			switch (opt) {
				case 's':
					ret = flock(flockFd, LOCK_SH);
					break;
				case 'e':
					ret = flock(flockFd, LOCK_EX);
					break;
				case 'u':
					ret = flock(flockFd, LOCK_UN);
					break;
				default:
					usage();
					exit(1);
			}
		}
		if (ret != 0) {
			perror("flock");
		}

		lseek(flockFd, -4, SEEK_END);
        read(flockFd, buffer, 4);
        sscanf(buffer, "%d", &offset);  // ASCII to integer.
        lseek(flockFd, offset, SEEK_END);
		memset(buffer, 0, sizeof(char) * BUF_SIZE);
        sprintf(buffer, "%d", offset + 1);  // integer to ASCII
		write(flockFd, buffer, 4);
        usleep(10000);  //sleep 0.01s
		fprintf(stderr, "Successfully write %d times.\r", i);
    }
	flock(flockFd, LOCK_UN);
	// printf("\n\nPress enter to end the process\n");
	// getchar();
	return 0;
}

void usage() {
	fprintf(stderr, "format error\n");
	fprintf(stderr, "./flock [s e u]\n");
	fprintf(stderr, "s: share lock\n");
	fprintf(stderr, "e: exclusive lock\n");
	fprintf(stderr, "u: unlock\n");
	fprintf(stderr, "default: exclusive lock\n");
	fprintf(stderr, "This program will create flock.db at ./bin\n");
}