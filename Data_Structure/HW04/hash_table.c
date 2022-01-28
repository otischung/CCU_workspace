#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    uint8_t *hashtable;
    uint32_t p, m, n;  // prime number, hash size (bits), # of ids
    uint32_t id, hv;
    uint8_t bias;

    scanf("%u %u %u", &p, &m, &n);
    hashtable = (uint8_t *)calloc((m - 1) / 8 + 1, sizeof(uint8_t));
    for (int i = 0; i < n; ++i) {
        scanf("%u", &id);
        hv = ((id * id) % p) % m;
        bias = hv % 8;
        bias = 1 << bias;
        hv /= 8;
        if ((hashtable[hv] & bias) == 0) {
            hashtable[hv] |= bias;
            printf("%u %u\n", id, 1);
        } else {
            printf("%u %u\n", id, 0);
        }
    }
    free(hashtable);
    return 0;
}
