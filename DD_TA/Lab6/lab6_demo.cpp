#include <bitset>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>


int main() {
    int a, b, s, p;
    srand(time(NULL));
    for (int i = 0; i < 3; ++i) {
        a = rand() % 16;
        b = rand() % 16;
        s = a + b;
        if (b > 7) {
            p = a * (b - 8);
        } else {
            p = a * b;
            if (p == 105) {
                p = 5;
            }
        }
        std::bitset<4> x(a);
        std::bitset<4> y(b);
        std::cout << "Input: 00 " << y << ' ' << x << '\n';
        std::cout << "Output: ";
        std::cout << std::setw(2) << std::setfill('0') << p << ' ';
        std::cout << std::setw(2) << std::setfill('0') << s << ' ';
        std::cout << std::setw(2) << std::setfill('0') << s << '\n';
    }
}
