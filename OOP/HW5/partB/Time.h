#pragma once
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

class Time {
    // Print time information in DAYS~HH:MM:SS format.
    friend std::ostream &operator<<(std::ostream &os, const Time &t);
    // Input time information in DAYS~HH:MM:SS format. If the format is illegal, set time to zero.
    friend std::istream &operator>>(std::istream &is, Time &t);
    
   private:
    std::int64_t days;
    int hours, minutes, seconds;

    // Set all parameters to zero.
    void setZero();
    // All parameters must be positive.
    void setTime(int64_t d, int h, int m, int s);
    // Make hours, minutes, seconds to be positive. days may be negative.
    void makePositive(int64_t &d, int &h, int &m, int &s);

   public:
    // Default constructor. It will set all parameters to zero.
    Time();
    // It will set "s" seconds and transfer it to correct format. If s is less than zero, then the time is zero.
    Time(const int &s);
    // Set all parameters and transfer it to correct format. If any of the parameters is less than zero, then the time is zero.
    Time(const int64_t &d, const int &h, const int &m, const int &s);
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
};

std::ostream &operator<<(std::ostream &os, const Time &t);
std::istream &operator>>(std::istream &is, Time &t);
