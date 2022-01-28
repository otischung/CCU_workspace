**Operating System Homework 11  資工3B 408410120 鍾博丞**

-----------------------------------------

## 環境配置

Operating System: Arch Linux 5.15.8-arch1-1 using KDE plasma

**CPU: AMD R9 3900X 12C 24T @ 3.8GHz**

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 451.3K IOPS, Random W: 325.6K IOPS)

## 解釋：sched_latency_ns 和 sched_min_granularity_ns

sched_latency_ns 為一個 cycle 裡面所有程式運行的時間，假設預設值為 18,000,000

sched_min_granularity_ns 為一個程式最少運行的時間，假設預設值為 2,250,000

由以上的預設值，在一個 time slice 裡面，可以放 8 個 processes。假設今天有 10 個 processes 進來，那麼 OS 會依據 sched_min_granularity_ns 的設定，延長 sched_latency_ns 至 22,500,000，避免 context-switch overhead 太大

似乎在 Arch Linux 裡面並沒有這兩項參數，故將 `sudo sysctl -a | grep kernel` 的執行結果附上

>kernel.sched_autogroup_enabled = 1 
>kernel.sched_cfs_bandwidth_slice_us = 5000 
>kernel.sched_child_runs_first = 0 
>kernel.sched_deadline_period_max_us = 4194304 
>kernel.sched_deadline_period_min_us = 100 
>kernel.sched_energy_aware = 1 
>kernel.sched_rr_timeslice_ms = 90 
>kernel.sched_rt_period_us = 1000000 
>kernel.sched_rt_runtime_us = 950000 
>kernel.sched_schedstats = 1 
>kernel.sched_util_clamp_max = 1024 
>kernel.sched_util_clamp_min = 1024 
>kernel.sched_util_clamp_min_rt_default = 1024

sched_rt_period_us 定義多長時間該被視為 100% 的 CPU 頻寬，單位為 us（「us」相當於「µs」）。預設值為 1000000µs，也就是 1 秒。

sched_rt_runtime_us 定義要給執行中的即時執行續之時間，單位為 us（「us」相當於「µs」）。預設值為 950000µs，也就是 0.95 秒。

其他可參閱 https://access.redhat.com/documentation/zh-cn/red_hat_enterprise_linux/7/html/performance_tuning_guide/sect-red_hat_enterprise_linux-performance_tuning_guide-cpu-configuration_suggestions

## 設計實驗,說明 context-switch 的次數與效能的關係

實作方法為更改 randAccess() 的敘述，詳見 [HW11.xlsx](./HW11.xlsx)

