#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
    bool *hashtable;
    uint32_t p, m, n;  // prime number, hash size (bits), # of ids
    uint32_t id, hv;

    scanf("%u %u %u", &p, &m, &n);
    hashtable = (bool *)calloc(m, sizeof(bool));
    for (int i = 0; i < n; ++i) {
        scanf("%u", &id);
        hv = ((id * id) % p) % m;
        if (hashtable[hv] == false) {
            hashtable[hv] = true;
            printf("%u %u\n", id, true);
        } else {
            printf("%u %u\n", id, false);
        }
    }
    free(hashtable);
    return 0;
}
