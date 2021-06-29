**System Programming Homework 03  資工2B 408410120 鍾博丞**

-----------------------------------------

### 環境配置

Operating System: Ubuntu 20.04 LTS using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

SSD: WD Black 256G WDS256G1X0C TLC (Seq. R: 2050MB/s, Seq. W: 700MB/s, Ran    dom R: 170K IOPS, Random W: 130K IOPS)

### 執行環境

執行`make`後，flock, lockf 會在 bin 資料夾裡，`cd` 進去就可以執行了，同時，裡面已經附上 `lockf_setting.sh` 和 `lockf_unlock.sh` 的 script，使用者只需執行 `sh lockf_setting.sh` 即可

in lockf_setting.sh

```shell
sudo mount -oremount,mand /
chmod g+s ./bin/lockf.db
chmod g-x ./bin/lockf.db
```

### 測試結果

```bash
time ./flock & time ./flock & time ./flock & time ./flock & 
time ./lockf l 0 10 &time ./lockf l 0 10 &time ./lockf l 0 10 &time ./lockf l 0 10 &
```

同時執行 4 個 flock 或 lockf 都是只能有一個 process 進行讀寫的

執行 4 個 flock 時，使用 vim 對其進行編輯，是可行的，因為 vim 不遵守 flock 的規則

![flock_executing](.//img/flock_executing.png)

![flock_end](.//img/flock_end.png)

但是，lockf 在執行當中，vim 若是強迫讀取是會直接卡死的

![lockf_executing](.//img/lockf_executing.png)

一定要等到 lockf 全部執行完畢後，vim 才能正常工作

![lockf_end](.//img/lockf_end.png)

以下是檔案實際大小 (只執行一次的大小)

![ls-lash](.//img/ls-lash.png)

因為我們每次只 lseek 3500 ~ 4000 byte，而一個 disk block 為 4096 byte，故無法生成有效的 file hole


最後的壓縮指令 
`tar jcvf filename.tar.bz2 target`