#include "neo.h"
#include "lazybox.h"
/*
 * return 0 for success end, other for fails
 */

static int chk() {
	static int last_chk = 0;
	int now = time(NULL);
	if (now - last_chk > 60) {
		if (!confirm()) return 0;
		last_chk = now;
	}
	return 1;
}

int lshell() {
	puts(" ::: Welcome to LazyShell! :::");
	const uid_t uid = getuid();
	const uid_t euid = geteuid();
	char *buf = GC_MALLOC(8192);
	if (getcwd(buf, 8192) == NULL) {
		return 1;	
	}
	while (1) {
		// seteuid(uid);
		// setuid(uid);
		// setfsuid(uid);
		printf("lazybox $ ");
		char **args = readline();
		if (args == nil) {puts("bye"); break;}
		char *prog = args[0];
		if (prog == nil) {
			continue;
		}
		if (str_eq("sudo", prog)) {
			if (args[1] == nil) {
				printf("usage: sudo <cmd> [...args]\n");
				continue;
			} else {
				seteuid(0);
				setuid(0);
				setfsuid(0);
				args++; // 從第一個參數開始
			}
		}
		if (str_eq(prog, "cd")) {
			if (args[1] == nil) {
				puts("usage: cd <dir>");
				continue;
			}
			if (chdir(args[1])) perror("can't cd");
			// system("pwd");
		} else if (str_eq(prog,  "exit")) {
			return 0;
		} else if (str_eq(prog, "chown")) {
			chk() && my_chown(args);	

		} else if (str_eq(prog, "clear")) {
			system("clear");
		} else {
			char *arg_string = GC_MALLOC(2 * 8192); // must safe coz readline max len 8192
			for (int i = 0; args[i] != nil; i++) {
				strcat(arg_string, args[i]);
				strcat(arg_string, " ");
			}
			system(arg_string);
		}
	}

	return 0;
}
