#include "Cube.h"

Cube::Cube() : x(0), y(0), z(0) {}

Cube::Cube(const double a, const double b, const double c) : x(a), y(b), z(c) {}

double operator/(const Cube &a, const Cube &b)  {
    return (a.x + a.y + a.z) / (b.x + b.y + b.z);
}

bool Cube::operator!=(const Cube &a) {
    return (this->x * this->y * this->z) != (a.x * a.y * a.z);
}
