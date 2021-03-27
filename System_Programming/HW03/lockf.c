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
	int lockfFd;
	int ret;  // check flock success (0) or not (-1)
	char buffer[BUF_SIZE];
    int offset;
	char opt;
	off_t begin, end;

	memset(buffer, 0, sizeof(char) * BUF_SIZE);
	
	if (argc != 4) {
		usage();
		exit(1);
	}

	lockfFd = open("./lockf.db", O_RDWR);
	if (lockfFd == -1) {
		// The file doesn't exist.
		lockfFd = open("./lockf.db", O_RDWR | O_CREAT | O_TRUNC);
		strcpy(buffer, "3500");
		write(lockfFd, buffer, strlen(buffer));
	}
	printf("lockfFd = %d is opened\n", lockfFd);
	
	sscanf(argv[1], "%c", &opt);
	sscanf(argv[2], "%ld", &begin);
	sscanf(argv[3], "%ld", &end);

	for (int i = 1; i <= 1000; ++i) {
		switch (opt) {
			case 'l':
				lseek(lockfFd, begin, SEEK_SET);
				ret = lockf(lockfFd, F_LOCK, end - begin + 1);
				break;
			case 'u':
				lseek(lockfFd, begin, SEEK_SET);
				ret = lockf(lockfFd, F_UNLCK, end - begin + 1);
				break;
			default:
				usage();
				exit(1);
		}
		if (ret != 0) {
			perror("lockf");
		}
		lseek(lockfFd, -4, SEEK_END);
        read(lockfFd, buffer, 4);
        sscanf(buffer, "%d", &offset);  // ASCII to integer.
        lseek(lockfFd, offset, SEEK_END);
		memset(buffer, 0, sizeof(char) * BUF_SIZE);
        sprintf(buffer, "%d", offset + 1);  // integer to ASCII
		write(lockfFd, buffer, 4);
        usleep(10000);  //sleep 0.01s
		fprintf(stderr, "Successfully write %d times.\r", i);
	}
	lockf(lockfFd, F_UNLCK, end - begin + 1);
	// printf("\n\nPress enter to end the process\n");
	// getchar();
	return 0;
}

void usage() {
	fprintf(stderr, "format error\n");
	fprintf(stderr, "./lockf [type(l/u)] [begin] [end]\n");
	fprintf(stderr, "l: lock\n");
	fprintf(stderr, "u: unlock\n");
	fprintf(stderr, "This program will create lockf.db at ./bin\n");
}