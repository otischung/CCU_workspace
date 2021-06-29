# DD Lab HW10 檔案操作事項

因為要求 mealy 和 moore 兩種實作，但是只有一個 testbench 很奇怪，故保留原本的 tb，新增兩個對應的 tb，就不用再特別修改 include file 和 function call

## makefile

### make

直接執行 make 將會實作 2 種方法，make 會自動執行 vvp 和 gtkwave 兩個程式

### make mealy

這將會實作 mealy，make 會自動執行 vvp 和 gtkwave 兩個程式

### make moore

這將會實作 moore，make 會自動執行 vvp 和 gtkwave 兩個程式

### make clean

這將會刪除所有 xxx_log.txt, xxx.vcd 與 bin 裡所有執行檔



**因為原本的 testbench 需要靠修改註解位置得到所需實作，故不推薦使用者直接操作 testbench.v 這個原始檔**

如果是使用 UNIX 系統或是在 Windows 有安裝 WSL 的話，**強烈建議使用 makefile**

