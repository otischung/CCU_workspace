#include "neo.h"
#include "lazybox.h"
/*
 * readline
 * returns:
 * 	NULL: EOF
 * 	others: string array split by space
 */
char** readline() {
	char buf[8192];
	char **arr = GC_MALLOC(100 * sizeof(char*));
	arr[0] = NULL;
	if (fgets(buf, 8192, stdin) == NULL) {
		return NULL;
	}
	char *str2 = NULL, *token = NULL, *subtoken = NULL;
	char *saveptr1 = NULL, *saveptr2 = NULL;
	int i = 0;
	for (str2 = buf; ; str2 = NULL) {
		subtoken = strtok_r(str2, " \r\n", &saveptr2);
		if (subtoken == NULL) break;
		arr[i] = GC_MALLOC(strlen(subtoken)+5);
		strcpy(arr[i++], subtoken);
		if (i >= 95) {
			break;
		}
		str2 = subtoken;
	}
	arr[i] = NULL;
	return arr;
}
