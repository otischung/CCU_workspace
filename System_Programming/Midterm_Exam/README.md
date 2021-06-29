**System Programming Midterm Exam  資工2B 408410120 鍾博丞**

-----------------------------------------

已完成全部

## 1, 7.

使用者執行 lazyshell，就等同於第一題的作法，makefile 會自動將 lazybox.c 以 --static 的方式編譯，而且會產生 lazyshell, ln, chown, stat 四個 soft link 到 lazybox

若直接執行 `./lazybox`，則與執行 `./lazyshell` 相同



## 2.

我印出 lazybox 的符號有做變化，讓它比較像 bash，也就是說，執行 lazyshell 時，提示符號為 lazybox:\<pwd\>$ 

```bash
lazybox:/home/pc341/mid2021$ cd ..
lazybox:/home/pc341$ cd .
lazybox:/home/pc341$ cd mid2021 
lazybox:/home/pc341/mid2021$ cd /home/pc341
lazybox:/home/pc341$ pwd
/home/pc341
lazybox:/home/pc341$ cd mid2021
lazybox:/home/pc341/mid2021$ ls
busybox  lazybox    lazyshell  makefile		README.md  test.txt
chown	 lazybox.c  ln	       make_tar.bz2.sh	stat
lazybox:/home/pc341/mid2021$
```

這樣更能表示當前 shell 所在目錄，也順便證實 lazybox 可以處理 cd 的四種要求



## 3.

執行 `./ln [-s] <old path> <new path>` 就可以產生 soft link 或 hard link



## 4. 

執行 `./stat <path_to_file>` 即可，並同時支援相對路徑和絕對路徑



## 5.

在 makefile 裡有 chown 和 chmod +s，搭配 setreuid() 就可以完成

執行 `./chown 0 <path_to_file>` 即可，並同時支援相對路徑和絕對路徑

## 6. 

先用 access 判斷 .sudo_success 存不存在，若不存在則立刻建立並且直接修改其 atime, mtime 為 0，這樣第一次執行就一定會問是否要執行

## 8. 

就是用 strncat 完成的



---------------------------------------------------------

最後的壓縮指令 
`tar jcvf filename.tar.bz2 target`