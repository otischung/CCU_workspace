**Object-Oriented Programming Homework 6**

---
## Author Information

Name: 鍾博丞

Student ID: 408410120

E-mail: my072814638@csie.io



## Environment

Operating System: Arch Linux 5.15.38-1-lts using KDE plasma

CPU: AMD R9 3900X 12C 24T @ 3.8GHz

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 390K IOPS, Random W: 380K IOPS)

g++: 

Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/12.1.0/lto-wrapper
Target: x86_64-pc-linux-gnu
Configured with: /build/gcc/src/gcc/configure --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++ --enable-bootstrap --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --with-linker-hash-style=gnu --with-system-zlib --enable-__cxa_atexit --enable-cet=auto --enable-checking=release --enable-clocale=gnu --enable-default-pie --enable-default-ssp --enable-gnu-indirect-function --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-multilib --enable-plugin --enable-shared --enable-threads=posix --disable-libssp --disable-libstdcxx-pch --disable-werror --with-build-config=bootstrap-lto --enable-link-serialization=1
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 12.1.0 (GCC)



 ## Compilation, Execution and Makefile

**We have provided a template called `main.cpp`**, you can modified it to use the program. `make` will help you compile all the test program.

All you need to do in `main.cpp` is listed below:

```c++
#include "GameHandle.h"

int main() {
    Game g;
    g.GameHandle();
    return 0;
}
```



First, you'll see the information below:

```
Welcome to play blackjack!!!
How many players you want to create:
```

Input a positive integer (min. players is 1). The Dealer is excluded.

Then you'll get the following information:

```
How many players you want to create: 5
Please enter the name or the type of bots.
There are two types of bots, which is Meek and Random.
If you want to create bot, just enter the type of bot.

Name:
```

If the name you type is not `Meek`, `meek`, `random`, `Random`, system will default to create human player named by the name you type.

If you type `Meek` or `meek`, theMeek bot will be created. Note that if you type `meEk` or others like this, system will create human player. Same as you type `Random` or `random`.

After you type the name, input their bankroll (min. is 1).

For example:

```
Name: otis 
Create otis human player.
Please enter otis's bankroll: Meek
Invalid input, try again: 100
Name: Meek
Create Meek bot.
Please enter Meek's bankroll: 1000
Name: Random
Create Random bot.
Please enter Random's bankroll: 200
Name: meek
Create Meek bot.
Please enter Meek's bankroll: 2000
Name: random
Create Random bot.
Please enter Random's bankroll: -1  
Warning: Your bankroll is less than 1. Default to 1.

The initial bankroll is listed below.
Dealer  $10000
otis    $100
Meek    $1000
Random  $200
Meek    $2000
Random  $1
```

Then, system will ask every human player how much you like to bet. (min. is 1)

```
Okay, time for betting.
--------------------------------
otis: how much would you like to bet? -1
Warning: Your bet is less than 1. Default to 1.
--------------------------------
otis bets $1
Meek bets $2
Random bets $41
Meek bets $2
Random bets $1

The initial starting cards are:
--------------------------------
Dealer's current hand: [??] [Q ♦] 
otis's current hand: [??] [1 ♥] 
Meek's current hand: [??] [J ♣] 
Random's current hand: [??] [5 ♦] 
Meek's current hand: [??] [1 ♥] 
Random's current hand: [??] [10 ♠]
```

Then, system will ask every human player if they want to hit (Y or y) or stand (input is not Y or y will default to stand).

Then you will see result

```
otis's turn:
--------------------------------
otis's current hand: [1 ♦] [1 ♥] (12 points)

Would you like to draw another card (Y or N): y
otis chooses to hit.
otis's current hand: [1 ♦] [1 ♥] [2 ♦] (14 points)

Would you like to draw another card (Y or N): y
otis chooses to hit.
otis's current hand: [1 ♦] [1 ♥] [2 ♦] [1 ♦] (15 points)

Would you like to draw another card (Y or N): y
otis chooses to hit.
otis's current hand: [1 ♦] [1 ♥] [2 ♦] [1 ♦] [4 ♣] (19 points)

Would you like to draw another card (Y or N): n
otis chooses to stand.

Meek's turn:
--------------------------------
Meek's current hand: [7 ♣] [J ♣] (17 points)

Meek has club 7 so it chooses to hit.
Meek's current hand: [7 ♣] [J ♣] [K ♦] (27 points)

Meek bust at 27.

Random's turn:
--------------------------------
Random's currents hand: [K ♥] [5 ♦] (15 points)

Random chooses to hit.
Random's currents hand: [K ♥] [5 ♦] [8 ♠] (23 points)

Random busts at 23.

Meek's turn:
--------------------------------
Meek's current hand: [6 ♦] [1 ♥] (17 points)

Meek chooses to stand.

Random's turn:
--------------------------------
Random's currents hand: [10 ♥] [10 ♠] (20 points)

Random chooses to stand.

Dealer's turn:
--------------------------------
Dealer's currents hand: [4 ♠] [Q ♦] (14 points)

Dealer chooses to hit.
Dealer's currents hand: [4 ♠] [Q ♦] [J ♠] (24 points)

Dealer busts at 24.

Let's see how it turned out:
--------------------------------
Yowzah! otis wins $1
Ouch! Meek loses $2
Ouch! Random loses $41
Yowzah! Meek wins $2
Yowzah! Random wins $1

The standings so far:
--------------------------------
Dealer  $10039
otis    $101
Meek    $998
Random  $159
Meek    $2002
Random  $2

Another round? (Y or N):
```

As same action above, input is not Y or y will default to N.



If anyone's bankroll is negative, the game will end automatically.



## Bonus Functions

When `cin` to integer number, we have provide error handling.

```c++
while (std::cin >> playerCnt, std::cin.fail()) {
    std::cerr << "Invalid input, try again: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

Reference: https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/

