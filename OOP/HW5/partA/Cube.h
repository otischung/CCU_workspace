#pragma once

class Cube {
   private:
    double x, y, z;

   public:
    Cube();
    Cube(const double a, const double b, const double c);
    friend double operator/(const Cube &a, const Cube &b);
    bool operator!=(const Cube &a);
};

double operator/(const Cube &a, const Cube &b);
