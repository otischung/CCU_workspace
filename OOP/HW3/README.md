**Object-Oriented Programming Homework 3**

---
## Author Information

Name: 鍾博丞

Student ID: 408410120

E-mail: my072814638@csie.io



## Environment

Operating System: Arch Linux 5.16.16-arch1-1 using KDE plasma

CPU: AMD R9 3900X 12C 24T @ 3.8GHz

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 390K IOPS, Random W: 380K IOPS)

gcc: 

Using built-in specs. 
COLLECT_GCC=gcc 
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/11.2.0/lto-wrapper 
Target: x86_64-pc-linux-gnu 
Configured with: /build/gcc/src/gcc/configure --enable-languages=c,c++, ada,fortran,go,lto,objc,obj-c++,d --enable-bootstrap --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --with-linker-hash-style=gnu --with-system-zlib --enable-__cxa_atexit --enable-cet=auto --enable-checking=release --enable-clocale=gnu --enable-default-pie --enable-default-ssp --enable-gnu-indirect-function --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-multilib --enable-plugin --enable-shared --enable-threads=posix --disable-libssp --disable-libstdcxx-pch --disable-werror --with-build-config=bootstrap-lto --enable-link-serialization=1 gdc_include_dir=/usr/include/dlang/gdc 
Thread model: posix 
Supported LTO compression algorithms: zlib zstd 
gcc version 11.2.0 (GCC)



## Items Implemented

### I/O specification

#### Input:

A floating point number. The number must be specified in argv[1]. That is, `./hw3 number`.

All the floating point number will be rounded to x.yz. For example: 3.11 -> 3.11; **3.119 -> 3.11**; 12.3 -> 12.30; 3. -> 3.00; .34 -> 0.34.

a.12 -> Format error; 2..3 -> Format error.



#### Output:

An equivalent number of *q* quarters, *d* dimes, *n* nikels, and *p* pennies, where *q*, *d*, *n*, *p* >= 0.

