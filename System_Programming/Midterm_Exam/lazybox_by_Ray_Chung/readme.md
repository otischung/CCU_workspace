**These code are written by Ray Chung**

# SP 期中考

# 1. Static Link

Built with `gcc ...objs --static`and verify with `readelf -d /bin/lazybox`

```bash
readelf -d bin/lazybox
There is no dynamic section in this file.
```

## 2. ChDIR

都寫好了

## 3. Link

也都寫好了

usage:

```bash
ln -s <src> <dst> // symlink
ln <src> <dst>    // hardlink
```



## 4. Stat

也都寫好了

```bash
stat <file>
```



## 5. Chown

也都寫好了



## 6. Chown+

也都寫好了



## 7. PATH

透過設定 path 的方式 (`setenv`)，讓 link 自己寫出來的檔案優先執行，找不到才會去找系統 PATH 下的。

