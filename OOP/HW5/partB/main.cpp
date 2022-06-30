#include "Time.h"

int main() {
    Time t1, t2, t3(123456), t4(987654321);
    std::cout << "t1 = " << t1 << '\n';
    std::cout << "t2 = " << t2 << '\n';
    std::cout << "t3 = " << t3 << '\n';
    std::cout << "t4 = " << t4 << '\n';
    std::cout << "Enter first Time object (DAYS~HH:MM:SS): ";
    std::cin >> t1;
    std::cout << "Enter second Time object (DAYS~HH:MM:SS): ";
    std::cin >> t2;
    std::cout << "\n\n";
    std::cout << t1 << " + " << t2 << " = " << t1 + t2 << '\n';
    std::cout << t1 << " - " << t2 << " = " << t1 - t2 << "\n\n";
    if (t1 < t2) std::cout << t1 << " < " << t2 << " is TRUE\n";
    if (t1 > t2) std::cout << t1 << " > " << t2 << " is TRUE\n";
    if (t1 <= t2) std::cout << t1 << " <= " << t2 << " is TRUE\n";
    if (t1 >= t2) std::cout << t1 << " >= " << t2 << " is TRUE\n";
    if (t1 == t2) std::cout << t1 << " == " << t2 << " is TRUE\n";
    if (t1 != t2) std::cout << t1 << " != " << t2 << " is TRUE\n\n";
    std::cout << t1 << " + 654321 = " << t1 + 654321 << '\n';
    std::cout << t2 << " + 15263748 = " << t2 + 15263748 << '\n';
    return 0;
}
