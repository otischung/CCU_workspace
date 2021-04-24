#include "neo.h"
#include "lazybox.h"

// helpers from homework
static void get_mtime(int fd, struct tm *tm) {
    struct stat statbuf;
    struct tm t;
    fstat(fd, &statbuf);
    tzset();
    localtime_r(&(statbuf.st_mtime), tm);
}
// 依樣畫葫蘆，不知道會不會爛掉
static void get_ctime(int fd, struct tm *tm) {
    struct stat statbuf;
    struct tm t;
    fstat(fd, &statbuf);
    tzset();
    localtime_r(&(statbuf.st_ctime), tm);
}

// 依樣畫葫蘆，不知道會不會爛掉
static void get_atime(int fd, struct tm *tm) {
    struct stat statbuf;
    struct tm t;
    fstat(fd, &statbuf);
    tzset();
    localtime_r(&(statbuf.st_atime), tm);
}


int my_stat(char** args) {
	char *filename = args[1];
	if (filename == nil) {
		printf("usage: %s <filename>\n", args[0]);
		return 1;
	}
	struct stat buf;
	int fd = open(args[1], O_RDONLY);
	if (fd < 0) {
		perror("開檔失敗");
		return 1;
	}
	struct tm mtime, ctime, atime;
	char mtime_str[8192], ctime_str[8192], atime_str[8192];
	get_mtime(fd, &mtime);
	get_ctime(fd, &mtime);
	get_atime(fd, &atime);
	strftime(atime_str, 8192, "%F %T", &atime);
	strftime(mtime_str, 8192, "%F %T", &mtime);
	strftime(ctime_str, 8192, "%F %T", &ctime);
	fstat(fd, &buf);
	uid_t uid = buf.st_uid;
	char *uname = getpwuid(uid)->pw_name;

	printf("owner:\t%s (%d)\n", uname, uid);
	printf("atime:\t%s\n", atime_str);
	printf("mtime:\t%s\n", mtime_str);
	printf("ctime:\t%s\n", ctime_str);

	return 0;
}
