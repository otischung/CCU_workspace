**AS HW04 CSIE 3B 408410120 鍾博丞**

- Algorithm use
    - Bubble sort

- C function use
	- malloc
	- sprintf
	- printf

- compiled with 
```bash
arm-none-eabi-gcc -g --specs=nosys.specs hw6_test.s numsort.s -o hw6.exe
```

- or with Makefile

```bash
make
```

- execute the program
```bash
arm-none-eabi-gdb ./hw6.exe
```

- or with Makefile
```bash
make run
```

and enter the following commands in GDB.

```gdb
(gdb) target sim
(gdb) load
(gdb) layout regs
(gdb) r
```

I use the data section to store 8 integers.

```assembly
.data
	.align 4

/* --- variable a --- */
	.type a, %object
	.size a, 32
a:
	.word 12
	.word 4
	.word 2
	.word 45
	.word 23
	.word 8
	.word 50
	.word 67
```

Thus, the output will be:

> Input array: 12 4 2 45 23 8 50 67 
> Output array: 2 4 8 12 23 45 50 67

This result will show at both stdout and file "result.txt".


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
