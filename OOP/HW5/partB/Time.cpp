#include "Time.h"

// Print time information in DAYS~HH:MM:SS format.
std::ostream &operator<<(std::ostream &os, const Time &t) {
    os << t.days << '~';
    os << std::setfill('0') << std::setw(2) << t.hours;
    os << ':';
    os << std::setfill('0') << std::setw(2) << t.minutes;
    os << ':';
    os << std::setfill('0') << std::setw(2) << t.seconds;
    return os;
}

// Input time information in DAYS~HH:MM:SS format. If the format is illegal, set time to zero.
std::istream &operator>>(std::istream &is, Time &t) {
    std::string input;
    std::string sd, sh, sm, ss;
    int64_t d;
    int h, m, s;
    size_t pos;

    is >> input;

    pos = input.find("~");
    if (pos == std::string::npos) {
        std::cerr << "Format error\nUsage: <day>~<hour>:<min>:<sec>, default to zero.\n";
        t.setZero();
        return is;
    }
    sd = input.substr(0, pos);
    input.erase(0, pos + 1);  // '~' has length 1

    pos = input.find(":");
    if (pos == std::string::npos) {
        std::cerr << "Format error\nUsage: <day>~<hour>:<min>:<sec>, default to zero.\n";
        t.setZero();
        return is;
    }
    sh = input.substr(0, pos);
    input.erase(0, pos + 1);  // ':' has length 1

    pos = input.find(":");
    if (pos == std::string::npos) {
        std::cerr << "Format error\nUsage: <day>~<hour>:<min>:<sec>, default to zero.\n";
        t.setZero();
        return is;
    }
    sm = input.substr(0, pos);
    input.erase(0, pos + 1);  // ':' has length 1

    ss = input;

    try {
        d = (int64_t)std::stoi(sd);
        h = std::stoi(sh);
        m = std::stoi(sm);
        s = std::stoi(ss);
    } catch (std::invalid_argument &e) {
        std::cerr << "Catched an error of invalid argument: " << e.what() << ", default to zero.\n";
        t.setZero();
        return is;
    }

    if (d < 0 || h < 0 || m < 0 || s < 0) {
        t.setZero();
    } else {
        t.setTime(d, h, m, s);
    }
    return is;
}

// Set all parameters to zero.
void Time::setZero() {
    days = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

// All parameters must be positive.
void Time::setTime(int64_t d, int h, int m, int s) {
    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    d += h / 24;
    h %= 24;

    days = d;
    hours = h;
    minutes = m;
    seconds = s;
}

// Make hours, minutes, seconds to be positive. days may be negative.
void Time::makePositive(int64_t &d, int &h, int &m, int &s) {
    if (s < 0) {
        --m;
        s += 60;
    }
    if (m < 0) {
        --h;
        m += 60;
    }
    if (h < 0) {
        --d;
        h += 24;
    }
}

// Default constructor. It will set all parameters to zero.
Time::Time() {
    setZero();
}

// It will set "s" seconds and transfer it to correct format. If s is less than zero, then the time is zero.
Time::Time(const int &s) {
    if (s < 0) {
        setZero();
    } else {
        setTime(0, 0, 0, s);
    }
}

// Set all parameters and transfer it to correct format. If any of the parameters is less than zero, then the time is zero.
Time::Time(const int64_t &d, const int &h, const int &m, const int &s) {
    if (d < 0 || h < 0 || m < 0 || s < 0) {
        setZero();
    } else {
        setTime(d, h, m, s);
    }
}

// Assign time class to "t" seconds.
void Time::operator=(const int &t) {
    if (t < 0) {
        setZero();
    } else {
        setTime(0, 0, 0, t);
    }
}

// Assign time class to the specific time class.
void Time::operator=(const Time &t) {
    days = t.days;
    hours = t.hours;
    minutes = t.minutes;
    seconds = t.seconds;
}

// Add "t" seconds to the time class.
Time Time::operator+(const Time &t) {
    Time ret;

    ret.days = days + t.days;
    ret.hours = hours + t.hours;
    ret.minutes = minutes + t.minutes;
    ret.seconds = seconds + t.seconds;
    ret.setTime(ret.days, ret.hours, ret.minutes, ret.seconds);
    return ret;
}

// Add two time classes.
Time Time::operator+(const int &t) {
    Time ret;

    ret.setTime(days, hours, minutes, seconds + t);
    return ret;
}

// Subtract "t" seconds to the time class.
Time Time::operator-(const int &t) {
    Time ret;
    int64_t d;
    int h, m, s;

    d = days;
    h = hours;
    m = minutes;
    s = seconds - t;

    makePositive(d, h, m, s);

    if (d < 0) {
        ret.setZero();
        return ret;
    } else {
        ret.setTime(d, h, m, s);
        return ret;
    }
}

// Subtrace two time classes.
Time Time::operator-(const Time &t) {
    Time ret;
    int64_t d;
    int h, m, s;

    d = days - t.days;
    h = hours - t.hours;
    m = minutes - t.minutes;
    s = seconds - t.seconds;

    makePositive(d, h, m, s);

    if (d < 0) {
        ret.setZero();
        return ret;
    } else {
        ret.setTime(d, h, m, s);
        return ret;
    }
}

bool Time::operator<(const Time &t) {
    if (days > t.days) return false;
    if (days < t.days) return true;
    if (hours > t.hours) return false;
    if (hours < t.hours) return true;
    if (minutes > t.hours) return false;
    if (minutes < t.minutes) return true;
    if (seconds >= t.seconds) return false;
    return true;
}

bool Time::operator>(const Time &t) {
    if (days < t.days) return false;
    if (days > t.days) return true;
    if (hours < t.hours) return false;
    if (hours > t.hours) return true;
    if (minutes < t.hours) return false;
    if (minutes > t.minutes) return true;
    if (seconds <= t.seconds) return false;
    return true;
}

bool Time::operator<=(const Time &t) {
    return !(*this > t);
}

bool Time::operator>=(const Time &t) {
    return !(*this < t);
}

bool Time::operator==(const Time &t) {
    if (days == t.days &&
        hours == t.hours &&
        minutes == t.minutes &&
        seconds == t.seconds) {
        return true;
    }
    return false;
}

bool Time::operator!=(const Time &t) {
    return !(*this == t);
}

// Prefix-increase statement, it will increase 1 second.
Time &Time::operator++() {
    setTime(this->days, this->hours, this->minutes, this->seconds + 1);
    return *this;
}

// Postfix-increase statement, it will increase 1 second.
const Time Time::operator++(const int t) {
    Time old = *this;
    setTime(this->days, this->hours, this->minutes, this->seconds + 1);
    return old;
}

// Prefix-decrease statement, it will decrease 1 second. If time is zero, then reamin zero.
Time &Time::operator--() {
    --seconds;
    makePositive(this->days, this->hours, this->minutes, this->seconds);
    if (days < 0) setZero();
    return *this;
}

// Postfix-decrease statement, it will decrease 1 second. If time is zero, then reamin zero.
const Time Time::operator--(const int t) {
    Time old = *this;
    --seconds;
    makePositive(this->days, this->hours, this->minutes, this->seconds);
    if (days < 0) setZero();
    return old;
}
