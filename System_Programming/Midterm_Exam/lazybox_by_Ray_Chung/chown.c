#include "neo.h"
#include "lazybox.h"
static inline void sudo() {
	seteuid(0);
	setuid(0);
	setfsuid(0);

}

int my_chown(char** args) {
	if (args == nil || args[1] == nil || args[2] == nil) {
		printf("usage: %s <uid> file\n", args[0]);
		return 1;
	}
	char* file = args[2];
	uid_t uid = atoi(args[1]);
	sudo();
	int ret = chown(file, uid, -1);
	if (ret) {
		perror("chown fail");
	} else {
		printf("%s's owner changed to %d\n", file, uid);
	}
	return ret;
}
