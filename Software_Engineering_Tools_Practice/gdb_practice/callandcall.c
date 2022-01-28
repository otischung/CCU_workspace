#include <stdio.h>

void FuncB(int X, int *Y);
void FuncA(int *X, int Y);

int main() {
    int X = 5;
    int Y = 10;
    FuncA(&X, Y);
    FuncB(X, &Y);

    return 0;
}

void FuncA(int *X, int Y) {
    Y += *X;
    Y *= *X + 10;
    return;
}

void FuncB(int X, int *Y) {
    X += 5;
    *Y = X + 20;
    *Y *= X + 20;
    return;
}
