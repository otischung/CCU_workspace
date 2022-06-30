#include <ctype.h>

#include <cmath>
#include <iostream>
#include <string>

class Coins {
   private:
    long long hundred_value;
    int quarters;  // 25 cents
    int dimes;     // 10 cents
    int nickels;   // 5 cents
    int pennies;   // 1 cent

    inline long long hundred(int x, int y, int z) {  // x.yz
        return (long long)(x * 100 + y * 10 + z);
    }

    inline void convert_to_cent(long long h, int &q, int &d, int &n, int &p) {
        q = h / 25;
        h %= 25;
        d = h / 10;
        h %= 10;
        n = h / 5;
        p = h % 5;
    }

    inline void convert_to_hundred(int &n, int &x, int &y, int &z) {
        x = n / 100;
        n %= 100;
        y = n / 10;
        z = n % 10;
    }

    bool check_str(std::string &str) {
        bool is_dot = false;
        for (std::size_t i = 0; i < str.length(); ++i) {
            if (!isdigit(str.at(i)) && str.at(i) != '.') {
                return false;
            }
            if (str.at(i) == '.') {
                if (!is_dot) {
                    is_dot = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }

   public:
    Coins(std::string &str) {
        std::size_t dot_location;
        int x, y, z;

        if (!check_str(str)) {
            throw std::invalid_argument("Format error.");
        }
        dot_location = str.find_first_of('.');
        if (dot_location == std::string::npos ||
            dot_location == str.length() - 1) {  // Can't find '.' or 1.
            x = std::stoi(str);
            y = 0;
            z = 0;
        } else if (dot_location == 0) {  // .xxx
            x = 0;
            if (str.length() == 2) {  // .2
                y = str.at(1) - '0';
                z = 0;
            } else {  // .23, .23xxx
                y = str.at(1) - '0';
                z = str.at(2) - '0';
            }
        } else if (dot_location == str.length() - 2) {  // 1.2
            x = std::stoi(str.substr(0, dot_location));
            y = str.at(dot_location + 1) - '0';
            z = 0;
        } else {  // 1.23
            x = std::stoi(str.substr(0, dot_location));
            y = str.at(dot_location + 1) - '0';
            z = str.at(dot_location + 2) - '0';
        }

        hundred_value = hundred(x, y, z);
        convert_to_cent(hundred_value, quarters, dimes, nickels, pennies);
    }
    Coins(double num) {
        int x, y, z, n;

        n = (int)std::floor(num * 100);
        convert_to_hundred(n, x, y, z);
        hundred_value = hundred(x, y, z);
        convert_to_cent(hundred_value, quarters, dimes, nickels, pennies);
    }
    Coins(int x, int y, int z) {
        hundred_value = hundred(x, y, z);
        convert_to_cent(hundred_value, quarters, dimes, nickels, pennies);
    }

    void print_result() {
        std::cout << "$" << hundred_value / 100 << "." << (hundred_value % 100) / 10 << hundred_value % 10
                  << " = " << quarters << " quarters, " << dimes << " dimes, "
                  << nickels << " nickels, " << pennies << " pennies.\n";
    }
};

int main(int argc, char **argv) {
    std::string input;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " x.yz\n";
        exit(1);
    }
    input = std::string(argv[1]);
    try {
        Coins c(input);
        c.print_result();
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
