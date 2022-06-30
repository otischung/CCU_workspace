#include <iostream>

#include "Grid.h"

using namespace std;

int main() {
    // check the grow function for work correctly
    Grid a;
    for (int i = 0; i < 5; i++) {
        a.Grow(2, 3);
        a.Grow(3, 2);
        a.Display();
    }
    // check the grow function for invalid input
    Grid b;
    b.Grow(100, 100);
    b.Display();
    b.Grow(-5, -5);
    b.Display();
    // check the grid constructor for initializing the mover's place
    Grid g(9, 15, -1, -2, Grid::WEST);
    g.Display();
    return 0;
}
