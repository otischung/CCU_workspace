#pragma once
#include <libgen.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/fsuid.h>

#include <gc.h>
#include <time.h>
#define malloc(a) GC_MALLOC((a))
#define calloc(a, b) GC_MALLOC((a)*(b))
#ifdef _DEBUG
#define DEBUG printf
#else
#define DEBUG
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE
#endif
#define str_eq(a, b) (!strcmp((a), (b)))
#define nil NULL // 寫太多 golang 了
#define strdup abort

extern char* LAZYPATH;
static inline void strip(char *buf) {
	if (buf == nil) return;
	if (buf[strlen(buf)-1] == '\n') {
		buf[strlen(buf)-1] = '\0';
	}
}

int ln(char **args);
