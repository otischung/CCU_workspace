# DD Lab HW09 檔案操作事項

因為要求 optimized serial multiplier 和 serial radix-4 booth multiplier 兩種實作，但是只有一個 testbench 很奇怪，故保留原本的 tb，新增兩個對應的 tb，就不用再特別修改 include file 和 function call

## makefile

### make

直接執行 make 將會實作 2 種方法，並將其執行檔放置於 bin 目錄裡，make 會自動執行 vvp 和 gtkwave 兩個程式，並將 vvp 產生的文字記錄到 xxx_log.txt 裡

### make osm

這將會實作 optimized serial multiplier，並將其執行檔放置於 bin 目錄裡，make 會自動執行 vvp 和 gtkwave 兩個程式，並將 vvp 產生的文字記錄到 osm_log.txt 裡

### make sr4bm

這將會實作 serial radix-4 booth multiplier，並將其執行檔放置於 bin 目錄裡，make 會自動執行 vvp 和 gtkwave 兩個程式，並將 vvp 產生的文字記錄到 sr4bm_log.txt 裡

### make clean

這將會刪除所有 xxx_log.txt, xxx.vcd 與 bin 裡所有執行檔



**因為原本的 testbench 需要靠修改註解位置得到所需實作，故不推薦使用者直接操作 tb_lab9_hw_unsigned.v 這個原始檔**

如果是使用 UNIX 系統或是在 Windows 有安裝 WSL 的話，**強烈建議使用 makefile**

