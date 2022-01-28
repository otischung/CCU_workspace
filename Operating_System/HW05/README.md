**Operating System Homework 05  資工3B 408410120 鍾博丞**

-----------------------------------------

## 環境配置

Operating System: Arch Linux 5.14.14-arch1-1 using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 451.3K IOPS, Random W: 325.6K IOPS)

## pi.c 操作

Usage: ./bin/pi [precise] [threads]

precise 為選填數值，預設為 10

threads 為選填數值，可以指定多少 threads 進行運算，如果不填則預設全核心運算

本次作業使用上下和求解 pi，預設核心全開 (24 threads)，使用 -O3 編譯，結果如下

| 精確度 | real time | user time  | sys. time |
| ------ | --------- | ---------- | --------- |
| 5      | 0.101     | 1.133      | 0.069     |
| 6      | 0.249     | 4.595      | 0.096     |
| 7      | 3.344     | 75.989     | 0.218     |
| 8      | 53.139    | 1223.454   | 1.124     |
| 9      | 3m29.748s | 82m16.242s | 2.145     |

real time 為程式之 turnaround time (time from start to finish of the call.)

user time 為程式執行之時間 * threads (the amount of CPU time spent in user-mode code (outside the kernel) *within* the process.)

sys time 為程式執行時所花費在 sys. call 上的時間 (the amount of CPU time spent in the kernel within the process.)

以下為精確度為 7 時的執行結果

| thread 數量 | real time | user time | sys. time |
| ----------- | --------- | --------- | --------- |
| 1           | 2.333     | 2.329     | 0.003     |
| 2           | 1.246     | 2.390     | 0.011     |
| 4           | 0.659     | 2.413     | 0.018     |
| 8           | 0.363     | 2.415     | 0.037     |
| 12          | 1.781     | 19.562    | 0.028     |
| 24          | 3.409     | 75.381    | 0.295     |

可以得到線性加速的效果，平行度很高，不過當 threads 數量上到 12 以上時，反而會有效能下降的效果

---

最後的壓縮指令

`tar jcvf filename.tar.bz2 target`

