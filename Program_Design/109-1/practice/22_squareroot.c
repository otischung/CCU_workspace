#include <stdio.h>
#define ll long long
double squareroot(ll num);

int main() {
    ll input;
    double answer;
    while (scanf("%lld", &input) != EOF) {
        answer = squareroot(input);
        printf("%lld\n", (ll)answer);
    }
    return 0;
}

double squareroot(ll num) {
    double t;
    double sqrtroot = num;
    do {
        t = sqrtroot;
        sqrtroot = (t + (num / t)) / 2;
    } while (t != sqrtroot);
    return sqrtroot;
}

/*
Newton's method
f(x) = x^2 - input
f'(x) = 2x
x1 = x0 - (f(x0) / f'(x0))
x1 = x0 - (x0^2 - input) / (2x0)
x1 = (2x0^2 - x0^2 + input) / 2x0
x1 = (x0^2 + input) / 2x0
x1 = (x0 + input / x0) / 2
*/