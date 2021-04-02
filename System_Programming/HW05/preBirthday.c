/**
DT_BLK      This is a block device. 「b」
DT_CHR      This is a character device. 「c」
DT_DIR      This is a directory. 「d」
DT_FIFO     This is a named pipe (FIFO). 「f」
DT_LNK      This is a symbolic link. 「l」
DT_REG      This is a regular file. 「-」
DT_SOCK     This is a UNIX domain socket. 「s」
DT_UNKNOWN  The file type could not be determined. 「U」
*/


#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>  // directory entry
#include <string.h>
#include <assert.h>
// 底下這個.h定義了最長的path name長度
#include <linux/limits.h>

// 檔案型別應該不會超過100個
bool filetype[128];
char fileSymbol[128];
long fileCnt = 0;

void usage(char *filename);
void initFileType();
int readSize(char *pathname);
long myCountDir(char *path);


/////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv[1]);
        exit(1);
    }

    setuid(0);
    initFileType();

    long totalsize;

    printf("授課老師 (羅習五) 的生日是: 1990/04/10\n");
    totalsize = myCountDir(argv[1]);
    printf("總共大小: %ld bytes\n", totalsize);
    printf("檔案種類: ");
    for (int i = 0; i < 127; ++i) {
        if (filetype[i]) {
            printf("%c", fileSymbol[i]);
        }
    }
    printf("\n總共檔案個數: %ld\n", fileCnt);

    return 0;
}
/////////////////////////////////////////////////////////////////


void usage(char *filename) {
    fprintf(stderr, "format error!!!\n");
    fprintf(stderr, "%s <path>\n\n", filename);
    fprintf(stderr, "This program can count many kinds of values of given path,\n");
    fprintf(stderr, "including total bytes, total amount of files, and species of all appeared file.\n\n");
    fprintf(stderr, "This program can only count 1 path.\n");
}

// 準備統計目錄中到底有多少種檔案型別，如果有該型別在filetype[X]上設定為1，該型別的代表字放在fileSymbol
void initFileType() {
    for (int i = 0; i < 127; ++i) {
        filetype[i] = false;
    }
    // DT_* is defined in dirent.h
    fileSymbol[DT_BLK]      = 'b';  // 6
    fileSymbol[DT_CHR]      = 'c';  // 2
    fileSymbol[DT_DIR]      = 'd';  // 4
    fileSymbol[DT_FIFO]     = 'f';  // 1
    fileSymbol[DT_LNK]      = 'l';  // 10
    fileSymbol[DT_REG]      = '-';  // 8
    fileSymbol[DT_SOCK]     = 's';  // 12
    fileSymbol[DT_UNKNOWN]  = 'U';  // 0
    // DT_WHT = 14
}

// 回傳某個檔案的大小
int readSize(char *pathname) {
    struct stat buf;
    // On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
    // https://blog.xuite.net/chowler/mainblog/5194764-assert%28%29+%E7%94%A8%E6%B3%95
    // assert()裡面填寫『我認為應該如此』，如果不是這樣的話，C函數庫會吐出錯誤訊息給programmer
    // 在這裡用lstat和stat都可以，因為pathname傳進來的只會是normal file，不會是「捷徑」（softlink）
    
    // printf("readSize: %s\n", pathname);
    assert(stat(pathname, &buf) == 0);
    return buf.st_size;

}

// 使用遞迴計算某個目錄中的所有正規檔案的大小，並統計到底有多少種檔案型別
// 如果沒有權限打開該打檔案怎麼辦？
// man access
/*       access() checks whether the calling process can access the file path‐
       name.  If pathname is a symbolic link, it is dereferenced.

       The mode specifies the accessibility check(s) to be performed, and is
       either  the value F_OK, or a mask consisting of the bitwise OR of one
       or more of R_OK, W_OK, and X_OK.  F_OK tests for the existence of the
       file.   R_OK,  W_OK, and X_OK test whether the file exists and grants
       read, write, and execute permissions, respectively.
*/
long myCountDir(char *path) {
    long size = 0; 
    // 打開該目錄
    DIR *dirp = opendir(path);
    // 讀取該目錄的第一個「物件」
    struct dirent *ent = readdir(dirp);
    /*
        The  readdir() function returns a pointer to a di‐
        rent structure representing the **next directory 
        entry** in the directory stream pointed to by dirp.
        It returns NULL on reaching the end of the direc‐
        tory stream or if an error occurred.
    */
    while (ent != NULL) {
        //『這個目錄』及『上一層目錄』跳過不處理
        if ( !strcmp(ent->d_name, "." ) || !strcmp(ent->d_name, ".." ) ) {
            ent = readdir(dirp);
            continue;
        }
        // 設定有這種檔案型別
        filetype[ent->d_type] = true;
        // 製造『路徑/名』
        // 如果使用者的輸入是「/」怎麼辦？，例如：「//home」會發生錯誤嗎？
        char pathname[PATH_MAX] = "";  // define PATH_MAX 4096 in limits.h
        strcat(pathname, path);
        strcat(pathname, "/");
        strcat(pathname, ent->d_name);
        // printf("%s\n", pathname);
        //如果是目錄
        if (ent->d_type == DT_DIR) {  // directory
            // printf("myCountDir: %s\n", pathname);
            //遞迴呼叫
            size += myCountDir(pathname);
        } else if (ent->d_type == DT_REG) {  // regular file
            size += readSize(pathname);
            ++fileCnt;
        }
        ent = readdir(dirp);
    }
    closedir(dirp);
    return size;
}