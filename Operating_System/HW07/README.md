**Operating System Homework 07  資工3B 408410120 鍾博丞**

-----------------------------------------

## 環境配置

Operating System: Arch Linux 5.14.11-arch1-1 using KDE plasma

CPU: Intel(R) Core(TM) i5-7300U CPU @ 2.60GHz

RAM: 4GB DDR4 

SSD: 128G

## Peterson's Solution

`./peterson_trival-g`

![01_peterson_trival-g.png](./img/01_peterson_trival-g.png)

`./peterson_trival-O3`

![02_peterson_trival-O3.png](./img/02_peterson_trival-O3.png)

`./peterson_correct-g`

![03_peterson_correct-g.png](./img/03_peterson_correct-g.png)

`./peterson_correct-O3`

![04_peterson_correct-O3.png](./img/04_peterson_correct-O3.png)

我們可以發現，`./peterson_trival-g` 與 `./peterson_trival-O3` 都是錯的，因為雙方在設定讓先時 `turn = 0 || turn = 1`，可能會同時動到，導致結果不正確

`./peterson_trival-g` 的速度比 `./peterson_correct-O3` 快，因為要正確執行需要使用 atomic operation，限制編譯器的優化，trivial 是快的，但是執行結果是錯的。
