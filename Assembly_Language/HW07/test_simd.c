#include <xmmintrin.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int A[8] __attribute__ ((aligned(16))) = {1, 2, 3, 4, 5, 6, 7, 8};
    int B[8] __attribute__ ((aligned(16))) = {1, 2, 3, 4, 5, 6, 7, 8};
    int C[8] __attribute__ ((aligned(16)));

    __m128 *a, *b, *c;

    a = (__m128 *)A;
    b = (__m128 *)B;
    c = (__m128 *)C;

    // *c++ = _mm_add_ps(*a++, *b++);
    // *c++ = _mm_add_ps(*a++, *b++);
    c[0] = _mm_add_ps(a[0], b[0]);
    c[1] = _mm_add_ps(a[1], b[1]);

    for (int i = 0; i < 8; ++i) {
        printf("%d%c", C[i], " \n"[i == 7]);
    }

    return 0;
}
