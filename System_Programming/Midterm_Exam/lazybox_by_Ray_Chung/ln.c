#include "neo.h"
#include "lazybox.h"

// 0 return for success
int ln(char **args) {
	if (args[1] == nil || args[2] == nil || (str_eq("-s", args[1]) && args[3] == nil)) {
		printf("usage: %s [-s] <src (must abs path)> <dst>\n", args[0]);
		return 1;
	}
	if (str_eq("-s", args[1])) {
		int r = symlink(args[2], args[3]);
		if (r) {
			perror("symlink failed");
		} else {
			printf("soft link created.\n");
			printf("%s ------> %s\n", args[2], args[3]);
		}
		return r;
	} else {
		// hardlink
		int r = link(args[1], args[2]);
		if (r) {
			perror("link failed");
		} else {
			printf("hard link created.\n");
			printf("%s ------> %s\n", args[1], args[2]);
		}
		return r;

	}
	return 0;
}
