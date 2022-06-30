#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>

const std::vector<std::vector<uint64_t>> mat = {
    {1, 1},
    {1, 0}
};

const std::vector<std::vector<uint64_t>> mat_1 = {
    {1, 0},
    {0, 1}
};

std::vector<std::vector<uint64_t>> mat_mul(std::vector<std::vector<uint64_t>> a, std::vector<std::vector<uint64_t>> b) {
    std::vector<std::vector<uint64_t>> ret;
    ret.resize(2, std::vector<uint64_t>(2, 0));

    ret[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    ret[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    ret[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    ret[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    return ret;
}

std::vector<std::vector<uint64_t>> mat_power(std::vector<std::vector<uint64_t>> a, uint64_t n) {
    if (n == 0) return mat_1;
    if (n == 1) return a;
    if (n % 2) {
        return mat_power(mat_mul(a, mat_power(a, n - 1)), 1);
    } else {
        return mat_power(mat_mul(a, a), n >> 1);
    }
}

int main(int argc, char **argv) {
    std::vector<std::vector<uint64_t>> fib;
    fib.resize(2, std::vector<uint64_t>(2, 0));
    uint64_t num;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " uint64_t: 0-92\n";
        exit(1);
    }
    if (!strcmp(argv[1], "--help")) {
        std::cerr << "Usage: " << argv[0] << " uint64_t: 0-92\n";
        exit(0);
    }
    num = atoi(argv[1]);
    if (num > 92) {
        std::cerr << "Exceed range of uint64_t, the answer is not correct.\n";
    }
    fib = mat_power(mat, num);
    // std::cout << fib[0][0] << '\t' << fib[0][1] << '\n' << fib[1][0] << '\t' << fib[1][1] << '\n';
    std::cout << "fib(" << num + 1 << ") = " << fib[0][0] << std::endl;
    std::cout << "fib(" << num << ") = " << fib[0][1] << std::endl;
    return 0;
}
