#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <linux/limits.h>  // PATH_MAX = PATH_MAX - 1

typedef struct inotify_event IE;
void usage(char *);
void printInotifyEvent(IE *);


//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    int fd, wd;
    ssize_t num;
    const size_t bufLen = 10 * sizeof(IE) + PATH_MAX + 1;
    char inotify_entity[bufLen];
    char *ieptr;

    // fd = open(argv[1], O_RDONLY, S_IRUSR);
    fd = inotify_init();
    wd = inotify_add_watch(fd, argv[1], IN_ALL_EVENTS);
    num = read(fd, inotify_entity, bufLen);

    while (true) {
        num = read(fd, inotify_entity, bufLen);
        ieptr = inotify_entity;

        while (ieptr < inotify_entity + num) {
            printInotifyEvent((IE *)ieptr);
            ieptr += sizeof(IE) + ((IE *)ieptr)->len;
        }
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////


void usage(char *program) {
    fprintf(stderr, "format error\n%s <file>\n", program);
}

void printInotifyEvent(IE *event) {
    char buf[PATH_MAX] = "";
    sprintf(buf, "[%d] ", event->wd);  // wd is int.
    strncat(buf, "{", PATH_MAX - 1);
    if (event->mask & IN_ACCESS)        strncat(buf, "ACCESS, ", PATH_MAX - 1);
    if (event->mask & IN_ATTRIB)        strncat(buf,"ATTRIB, ", PATH_MAX - 1);
    if (event->mask & IN_CLOSE_WRITE)   strncat(buf,"CLOSE_WRITE, ", PATH_MAX - 1);
    if (event->mask & IN_CLOSE_NOWRITE) strncat(buf,"CLOSE_NOWRITE, ", PATH_MAX - 1);
    if (event->mask & IN_CREATE)        strncat(buf,"CREATE, ", PATH_MAX - 1);
    if (event->mask & IN_DELETE)        strncat(buf,"DELETE, ", PATH_MAX - 1);
    if (event->mask & IN_DELETE_SELF)   strncat(buf,"DELETE_SELF, ", PATH_MAX - 1);
    if (event->mask & IN_MODIFY)        strncat(buf,"MODIFY, ", PATH_MAX - 1);
    if (event->mask & IN_MOVE_SELF)     strncat(buf,"MOVE_SELF, ", PATH_MAX - 1);
    if (event->mask & IN_MOVED_FROM)    strncat(buf,"MOVED_FROM, ", PATH_MAX - 1);
    if (event->mask & IN_MOVED_TO)      strncat(buf,"MOVED_TO, ", PATH_MAX - 1);
    if (event->mask & IN_OPEN)          strncat(buf,"OPEN, ", PATH_MAX - 1);
    if (event->mask & IN_IGNORED)       strncat(buf,"IGNORED, ", PATH_MAX - 1);
    if (event->mask & IN_ISDIR)         strncat(buf,"ISDIR, ", PATH_MAX - 1);
    if (event->mask & IN_Q_OVERFLOW)    strncat(buf,"Q_OVERFLOW, ", PATH_MAX - 1);
	buf[strlen(buf) - 2] = '\0';
	strncat(buf, "}", PATH_MAX - 1);
    snprintf(buf, PATH_MAX - 1, "%s cookie = %d", buf, event->cookie);

    if (event->len > 0)
        snprintf(buf, PATH_MAX - 1, "%s name = %s\n", buf, event->name);
    else
        snprintf(buf, PATH_MAX - 1, "%s name = null\n", buf);

    printf("%s", buf);
}
