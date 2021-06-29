# HW02
# 檢查記憶體相關問題
sudo apt install -y valgrind
# GUI 界面版本
sudo apt install -y kcachegrind
#perf
sudo apt install -y linux-tools-common
sudo apt install -y linux-tools-5.8.0-50-generic
sudo apt install -y linux-cloud-tools-5.8.0-50-generic

# perf
sudo apt-get install linux-tools-common
# HW04
# utrace: gcc -pg
# ltrace: -z lazy

# HW05
# 

# HW06 busybox
# git clone https://git.busybox.net/busybox/
# 這是 make menuconfig 時需要的函數庫
sudo apt install -y libncurses5-dev
# cd busybox
# make defconfig
# make menuconfig
# make
# make install
# sudo chroot ~/busybox/_install/ ash
# cd ..

# HW07
# ACL = access control list
sudo apt install -y libacl1-dev
# inotify 監控檔案或目錄的讀寫
sudo apt install -y inotify-tools
# ACL GUI
sudo apt install -y eiciel
sudo apt install -y acl acl-dev
sudo apt install -y clang
# 擴充屬性
sudo apt install -y attr
# 另一種 debugger，這是基於 KDE 的函數庫寫出來的程式，故程式雖小，安裝需花較多時間
# sudo apt install -y kdbg
# 試用 inotify
sudo apt install -y inotify-tools
# pthread manpage
sudo apt install manpages-posix manpages-posix-dev
