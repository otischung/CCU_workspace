#include "neo.h"
#include "lazybox.h"

/*
 * return: 1 yes, 0 no
 * */
int confirm() {
REDO:
	printf("你要執行的是特權指令,確定的話,請輸入『yes』,否則按下『enter』終止操作：");
	char *buf = GC_MALLOC(8192);
	fgets(buf, 8192, stdin);
	strip(buf);
	if (buf == NULL) return 0;
	if (str_eq(buf, "")) {
		return 0;
	}
	if (str_eq(buf, "yes")) {
		return 1;	
	}
	else {
		goto REDO;
	}
	return 0;
	
}
