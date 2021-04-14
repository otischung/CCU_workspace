#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <linux/limits.h>  // PATH_MAX = 4096

typedef struct inotify_event IE;
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

    fd = inotify_init();
    wd = inotify_add_watch(fd, argv[1], IN_ALL_EVENTS);

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
    sprintf(buf, "[%s] ", event->wd);
    strncat(buf, "{", PATH_MAX);
    if (event->mask & IN_ACCESS)        strncat(buf, "ACCESS, ", 4096);
    if (event->mask & IN_ATTRIB)        strncat(buf,"ATTRIB, ", 4096);
    if (event->mask & IN_CLOSE_WRITE)   strncat(buf,"CLOSE_WRITE, ", 4096);
    if (event->mask & IN_CLOSE_NOWRITE) strncat(buf,"CLOSE_NOWRITE, ", 4096);
    if (event->mask & IN_CREATE)        strncat(buf,"CREATE, ", 4096);
    if (event->mask & IN_DELETE)        strncat(buf,"DELETE, ", 4096);
    if (event->mask & IN_DELETE_SELF)   strncat(buf,"DELETE_SELF, ", 4096);
    if (event->mask & IN_MODIFY)        strncat(buf,"MODIFY, ", 4096);
    if (event->mask & IN_MOVE_SELF)     strncat(buf,"MOVE_SELF, ", 4096);
    if (event->mask & IN_MOVED_FROM)    strncat(buf,"MOVED_FROM, ", 4096);
    if (event->mask & IN_MOVED_TO)      strncat(buf,"MOVED_TO, ", 4096);
    if (event->mask & IN_OPEN)          strncat(buf,"OPEN, ", 4096);
    if (event->mask & IN_IGNORED)       strncat(buf,"IGNORED, ", 4096);
    if (event->mask & IN_ISDIR)         strncat(buf,"ISDIR, ", 4096);
    if (event->mask & IN_Q_OVERFLOW)    strncat(buf,"Q_OVERFLOW, ", 4096);
	buf[strlen(buf) - 2] = '\0';
	strncat(buf, "}", 4096);
    sprintf(buf, "%s cookie = %d", buf, event->cookie);

    if (event->len > 0)
        sprintf(buf, "%s name = %s\n", buf, event->name);
    else
        sprintf(buf, "%s name = null\n", buf);

    printf("%s", buf);
}
