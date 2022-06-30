**Object-Oriented Programming Homework 4**

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



 ## Compilation and Makefile

**We have provided a template called `main.cpp`, you can modified it to use the program. `make test` will help you compile the test program.**

We also have provided an example called `hw4.cpp`. The example is from the slides. We have precompiled it to `hw4` with `-O3 --static` flags.



## Exection

Modify `test.cpp` and use `Makefile` (`make test`) to run the program.


## Functions Behaviors

1. Constructor `Grid();` will build 1 x 1 grid with mover in only square, facing east. And without any block, of course.

   ```
   >
   ```

2. Constructor `Grid(int r, int c);` will build *r* \* *c* grid and random mover position and direction, notice that the mover will never initialize at exit. **If any value of *r* or *c* is less than 3 will be set as 3**; if any value of *r* or *c* is greater than MAXSIZE, which is defined in `Grid.h`, will be set as MAXSIZE.

3. Constructor `Grid(int r, int c, int mr, int mc, int d);` will build *r* \* *c* grid as like in 2-param constructor, and set the mover's direction *d*. **However, the minimum in this case is 1**.

   If r and c are all greater or equal to 3, then the constructor will generate wall at edge automatically. In this case, the mover's position (*mr*, *mc*) cannot be set at the edge position.

   Otherwise, there is no wall at edge and thus the mover's position is allowed to put at the edge position.

   If the position is illegal, set the nearest legal position to mover.

   The exit position is random.

4. **Bonus constructor** `Grid::Grid(int r, int c, int mr, int mc, int d, int er, int ec)` will build *r* \* *c* grid as like in 5-param constructor, and let user specific the exit position (*er*, *ec*). The exit position must be at the edge of the grid and can't be at the corner position. **If the exit position is illegal, the exit position is random**.

5. The function `bool Grow(int gr, int gc);` will keep the original **exit** position if the position is at the left or the top edge. If the original exit position is at the right edge, the new position will be extend at the same row, still at the right edge; if the original exit position is at the bottom edge, the new position will be extend at the same column, still at the bottom edge. That is, 

   ```c++
   Grid g(4, 4, 1, 1, Grid::NORTH, 1, 3);
   g.Display();
   g.Grow(5, 5);
   g.Display();
   ```

   will be 

   ```
   # # # # 
   # ^ . # 
   # . . # 
   # . # # 
   
   # # # # # # # # # 
   # ^ . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . # # # # # # #
   ```

   , and 

   ```c++
   Grid g(4, 4, 1, 1, Grid::NORTH, 3, 1);
   g.Display();
   g.Grow(5, 5);
   g.Display();
   ```

   will be

   ```
   # # # # 
   # ^ . # 
   # . . # 
   # . # # 
   
   # # # # # # # # # 
   # ^ . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . . . . . . . # 
   # . # # # # # # #
   ```

   This function will keep the wall state. That is, if the original grid is 2\*2, which has no wall at the edge, the new grid greater than 3\*3 still has no wall.

6. **Bonus function** `bool RemoveBlock(int r, int c);` will remove a block at place (*r*, *c*). If there is no block, the function will return false.

7. **\[Important\]** These functions

   ```c++
   bool PutDown(int r, int c);
   bool PlaceBlock(int r, int c);
   bool RemoveBlock(int r, int c);
   ```

   will throw `std::out_of_range` exception if the position (*r*, *c*) is out of range.

   Therefore, when you use these function, you have to catch these exception by yourself. Otherwise, the process will receive SIGIOT, which is same as SIGABRT.

   Below is the sample code to catch exceptions:

   ```c++
   Grid g(4, 4);
   try {
       g.RemoveBlock(100, 100);
   } catch (std::exception &e) {
       std::cerr << e.what() << std::endl;
   }
   ```

   

## Bonus

We provide 7 parameters constructor to let user set exit position. The constructor is described above.

We provide RemoveBlock function.

If the grid is no less than 3\*3, then we will produce blocks at the edge automatically.

The exit will be extended while using `bool Grow(int gr, int gc);` with exit is at the right or the bottom place of the grid.

