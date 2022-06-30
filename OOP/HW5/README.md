**Object-Oriented Programming Homework 5**

---
## Author Information

Name: 鍾博丞

Student ID: 408410120

E-mail: my072814638@csie.io



## Environment

Operating System: Arch Linux 5.17.5-arch1-1 using KDE plasma

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



 ## Compilation, Execution and Makefile

**We have provided a template called `main.cpp`**, you can modified it to use the program. `make` will help you compile all the test program.



## Part A: Cube

There are three private double variables *x*, *y*, and *z*.

The constructor needs 3 parameters, input 3 double parameters will initial these variables.

If you don't provide any parameter, the variables will all initial to 0 by default.

There is a *friend function* overloading `/`, which divides the sum of the members *x*, *y*, and *z* in the first object by the sum of the corresponding members in the second object and return the result as double.

There is a *member function* overloading `!=`, which test if the volume of the first object is not equal the
volume of the second object. The volume of a cube is *x* \* *y* \* *z*.



## Part B: Time

There are 4 private variables.

```c++
std::int64_t days;
int hours, minutes, seconds;
```

We have provide 3 constructors.

```c++
// Default constructor. It will set all parameters to zero.
Time();
// It will set "s" seconds and transfer it to correct format. If s is less than zero, then the time is zero.
Time(const int &s);
// Set all parameters and transfer it to correct format. If any of the parameters is less than zero, then the time is zero.
Time(const int64_t &d, const int &h, const int &m, const int &s);
```

We have overload these operators.

```c++
// Assign time class to "t" seconds.
void operator=(const int &t);
// Assign time class to the specific time class.
void operator=(const Time &t);
// Add "t" seconds to the time class.
Time operator+(const int &t);
// Add two time classes.
Time operator+(const Time &t);
// Subtract "t" seconds to the time class.
Time operator-(const int &t);
// Subtrace two time classes.
Time operator-(const Time &t);

bool operator<(const Time &t);
bool operator>(const Time &t);
bool operator<=(const Time &t);
bool operator>=(const Time &t);
bool operator==(const Time &t);
bool operator!=(const Time &t);

// Prefix-increase statement, it will increase 1 second.
Time &operator++();
// Postfix-increase statement, it will increase 1 second.
const Time operator++(const int t);
// Prefix-decrease statement, it will decrease 1 second. If time is zero, then reamin zero.
Time &operator--();
// Postfix-decrease statement, it will decrease 1 second. If time is zero, then reamin zero.
const Time operator--(const int t);
```

And also overload ostream (cout) and istream (cin).

```c++
// Print time information in DAYS~HH:MM:SS format.
friend std::ostream &operator<<(std::ostream &os, const Time &t);
// Input time information in DAYS~HH:MM:SS format. If the format is illegal, set time to zero.
friend std::istream &operator>>(std::istream &is, Time &t);
```



## Bonus Functions

```c++
// Add "t" seconds to the time class.
Time operator+(const int &t);
// Subtract "t" seconds to the time class.
Time operator-(const int &t);
```

