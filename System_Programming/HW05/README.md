**System Programming Homework 05  資工2B 408410120 鍾博丞**

-----------------------------------------

### 環境配置

Operating System: Ubuntu 20.04 LTS using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

SSD: WD Black 256G WDS256G1X0C TLC (Seq. R: 2050MB/s, Seq. W: 700MB/s, Random R: 170K IOPS, Random W: 130K IOPS)

### 執行環境

執行`sudo make`後，preBirthday 會在 bin 資料夾裡，`cd` 進去就可以執行了

因為是 sudo make，所以 不需要 `sudo chown root preBirthday`，在 sudo mode 下 make 一定是 root 權限，包含 bin 資料夾，故只需加入 set-uid 即可

因為 bin 資料夾權限皆為 root，故刪除時也需使用 sudo，即 `sudo make clean`

in makefile

```make
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	mkdir -p ./bin
	${CC} ${CFLAGS} $@.c -o ./bin/$@
	sudo chmod +s ./bin/$@

clean:
	rm -f ./bin/*
```



### 測試結果

```c
DIR *dirp = opendir(path);
```

如果在開檔時沒有檢查是否開檔成功的話，遇到  pseudo file，會無法開啟，就算是 root 也無法喔

如果沒有檢查就執行，會出現 segmentation fault

我們用 gdb 看一下

```bash=
...
myCountDir: //run/user
//run/user/127
myCountDir: //run/user/127
//run/user/127/gvfs
myCountDir: //run/user/127/gvfs

Program received signal SIGSEGV, Segmentation fault.
0x00007f26e4f7c4a4 in __lll_cas_lock (futex=0x4) at ../sysdeps/unix/sysv/linux/x86/lowlevellock.h:47
47      ../sysdeps/unix/sysv/linux/x86/lowlevellock.h: 沒有此一檔案或目錄.
(gdb) bt
#0  0x00007f26e4f7c4a4 in __lll_cas_lock (futex=0x4) at ../sysdeps/unix/sysv/linux/x86/lowlevellock.h:47
#1  __GI___readdir64 (dirp=0x0) at ../sysdeps/posix/readdir.c:44
#2  0x0000563fc2156645 in myCountDir (path=0x7fffcdefc020 "//run/user/127/gvfs") at preBirthday.c:135
#3  0x0000563fc2156788 in myCountDir (path=0x7fffcdefd070 "//run/user/127") at preBirthday.c:182
#4  0x0000563fc2156788 in myCountDir (path=0x7fffcdefe0c0 "//run/user") at preBirthday.c:182
#5  0x0000563fc2156788 in myCountDir (path=0x7fffcdeff110 "//run") at preBirthday.c:182
#6  0x0000563fc2156788 in myCountDir (path=0x7fffcdf00dcd "/") at preBirthday.c:182
#7  0x0000563fc21563ba in main (argc=2, argv=0x7fffcdf00248) at preBirthday.c:54
```

pseudo file，也只有 owner 才能開啟，就算是 root 也沒辦法，舉例，我們用 perror 抓出是哪個檔案開不起來

```bash=
//run/user/127/gvfs: Permission denied
//run/user/1000/doc: Permission denied
//run/user/1000/gvfs: Permission denied
```

這些就是 pseudo file/directory 了



## 測量誤差

測量根目錄時，每次測量的結果都不太相同，都會有些許誤差，誤差值約在 0.15% 左右

若是不測量系統檔，只測量自己家目錄下的檔案或目錄，則不會有誤差



---------------------------------------------------------

最後的壓縮指令 
`tar jcvf filename.tar.bz2 target`