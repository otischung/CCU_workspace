// This code is written by Ray Chung
#include "neo.h"
#include "lazybox.h"
int main(int argc, const char *argv[]) {
	GC_INIT();
	GC_enable_incremental();
	const char * const path = getenv("PATH");
	char *cwd = GC_MALLOC(8192);
	getcwd(cwd, 8192);
	char *new_path = malloc(strlen(path) + strlen(argv[0]) + 10);
	new_path[0] = '\0';
	char *dir = GC_MALLOC(strlen(argv[0]+5));
	strcpy(dir, argv[0]);
	const char * const lazy_dir = dirname(dir);
	if (lazy_dir[0] != '/') {
		strcat(new_path, cwd);
		strcat(new_path, "/"); // calc rel path
	}
	strcat(new_path, lazy_dir);  
	strcat(new_path, ":");
	strcat(new_path, path);
	// printf("PATH: %s\n", new_path);
	// 把目錄加到 PATH 這樣自己的可執行就會優先
	setenv("PATH", new_path, 1);
	assert(argc < 95);
	// adapt for lazy shell's args
	char **args = GC_MALLOC(95 * sizeof(char*));
	for (int i = 0; i < argc; i++) {
		args[i] = malloc(strlen(argv[i]+5));
		strcpy(args[i], argv[i]);
	}
	args[0] = basename(args[0]);
	// printf("prog: '%s'\n", args[0]);

	char **new_argv = GC_MALLOC(sizeof(char*) * 100);
	if (str_eq("ln", args[0])) {
		return ln(args);
	} else if (str_eq("stat", args[0])) { 
		return my_stat(args);
	} else if (str_eq("lazysh", args[0]) || str_eq("lazyshell", args[0]) || str_eq("lazybox", args[0])){
		return lshell();
	}
	lshell();
	return 0;
}
