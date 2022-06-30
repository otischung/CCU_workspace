#include "Cube.h"

#include <iostream>

int main() {
    Cube c1(2.0, 3.0, 4.0);
    Cube c2(2.0, 3.0, 4.0);
    std::cout << c1 / c2 << std::endl;
    c1 != c2 ? std::cout << "Not equal.\n" : std::cout << "Equal.\n";
    return 0;
}
