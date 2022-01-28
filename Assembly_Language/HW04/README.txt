**AS HW04 CSIE 3B 408410120 鍾博丞**

- Algorithm use
    - Bubble sort

- compiled with 
```bash
arm-none-eabi-gcc -g --specs=nosys.specs hw4_test.s numsort.s -o hw4.exe
```

- execute the program
```bash
arm-none-eabi-gdb ./hw4.exe
```

```gdb
(gdb) target sim
(gdb) load
(gdb) layout regs
(gdb) b main
(gdb) b 53
(gdb) r
(gdb) c
(gdb) i r
(gdb) p *(address recorded in r1)
(gdb) p *(address recorded in r1 + 4)
(gdb) p *(address recorded in r1 + 8)
(gdb) p *(address recorded in r1 + 12)
(gdb) p *(address recorded in r1 + 16)
(gdb) p *(address recorded in r1 + 20)
(gdb) p *(address recorded in r1 + 24)
(gdb) p *(address recorded in r1 + 28)
```

- The environment of compiling program
```bash
arm-none-eabi-gcc -v
```

Using built-in specs.
COLLECT_GCC=arm-none-eabi-gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/arm-none-eabi/11.2.0/lto-wrapper
Target: arm-none-eabi
Configured with: /build/arm-none-eabi-gcc/src/gcc-11.2.0/configure --target=arm-none-eabi --prefix=/usr --with-sysroot=/usr/arm-none-eabi --with-native-system-header-dir=/include --libexecdir=/usr/lib --enable-languages=c,c++ --enable-plugins --disable-decimal-float --disable-libffi --disable-libgomp --disable-libmudflap --disable-libquadmath --disable-libssp --disable-libstdcxx-pch --disable-nls --disable-shared --disable-threads --disable-tls --with-gnu-as --with-gnu-ld --with-system-zlib --with-newlib --with-headers=/usr/arm-none-eabi/include --with-python-dir=share/gcc-arm-none-eabi --with-gmp --with-mpfr --with-mpc --with-isl --with-libelf --enable-gnu-indirect-function --with-host-libstdcxx='-static-libgcc -Wl,-Bstatic,-lstdc++,-Bdynamic -lm' --with-pkgversion='Arch Repository' --with-bugurl=https://bugs.archlinux.org/ --with-multilib-list=rmprofile
Thread model: single
Supported LTO compression algorithms: zlib zstd
gcc version 11.2.0 (Arch Repository)
