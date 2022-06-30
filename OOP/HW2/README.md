****Object-Oriented Programming Homework 2**

---
## Author Information

Name: 鍾博丞

Student ID: 408410120

E-mail: my072814638@csie.io



## Environment

Operating System: Arch Linux 5.16.12-arch1-1 using KDE plasma

CPU: AMD R9 3900X 12C 24T @ 3.8GHz

RAM: 32GB DDR4 3600MHz (Double channel)

SSD: ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 390K IOPS, Random W: 380K IOPS)



## Items Implemented

### I/O specification

#### Input:

A file. The filename must be specified in argv[1]. That is, `./hw2 <filename>`.

Each line in the file contains a card number to check its validation or `004`, `005`, `0037`, `006` for generating Visa, MasterCard, American Express and Discover card, respectively.



#### Output:

Information of validation of a card number, or output a pseudo card number.



### Functions Implemented

```c++
bool isValid(const string &cardNumber);  // Line 133
int sumofDoubleEvenPlace(const std::string &cardNumber);  // Line 21
int sumOfOddPlace(const std::string &cardNumber);  // Line 41
std::string fake_one(int brand);  // Line 147
```



### Functions Not Implemented

```c++
// Return this number if it is a single digit, otherwise,
// return the sum of the two digits.
int getDigit(int number);
```

Just sum up of the odd number and the even number. I think it is unnecessary.

```c++
// Return true if substr is the prefix for cardNumber
bool startsWith (const string &cardNumber, const string &substr)
```

The prefixes (substrings) of different brand have different length and defferent rules. It is too complex to predefine a suitable substring.



### Time Measurement

Since the time cost of the pseudo card number generator can generate a valid card number less than 1 micorsecond, `clock_gettime(CLOCK_MONOTONIC, &start);` in `time.h` is used in this project. This function can measure time in nanosecond.



### Algorithm of Pseudo Card Number Generator

Let's take a look of 4556443985096249

First, add odd place of the string from right to left, we will get 9+2+9+5+9+4+6+5=49.

Next, add even place of the string from right to left, double each number, if the doubled number is greater than 9, then split to two digit and add them together. We will get 8+(1+2)+0+(1+6)+6+8+(1+0)+8=41

Add them together, we will get 49+41=90, which can be divided by 10.



Since calculate the sum of digits in the odd place is easiser, we take a look of the last digit.

Let's say we want to generate a pseudo Visa card. The first digit must be 4. Then generate random digits without the last digit. Suppose we have generate 455644398509624x, 0 <= x <= 9, we will get 40+x+41 (mod 10) = 81+x (mod 10) must be 0, [(81 mod 10) + (x mod 10)] mod 10 = 1 + x (mod 10). Since 0 <= x <= 9, we know that x = 9.

Generally, suppose that other digits calculation modulo 10 is y, then we want to solve y+x mod 10 = 0. y is any positive number modulo 10, so 0 <= y <= 9; x is in odd place, so 0 <= x <= 9. If y = 0, then x = 0; if 1 <= y <= 9, then x = 10 - y.

To sum up, let x = 0 to calculate y, then pop x = 0, push correct x back.



## Bonus

The rules of credit card number used in this program is listed below.



## Reference

### Rules of Credit Card Number

https://www.mobilefish.com/services/credit_card_number_generator/credit_card_number_generator.php
https://en.wikipedia.org/wiki/Payment_card_number
