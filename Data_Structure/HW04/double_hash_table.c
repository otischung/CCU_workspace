#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reference: https://www.itread01.com/content/1547623280.html
///////////////////////////////////////////////////////////////////////
#define ZDBG 0
#define SHFR(x, n) (((x) >> (n)))
#define ROTR(x, n) (((x) >> (n)) | ((x) << ((sizeof(x) << 3) - (n))))
#define ROTL(x, n) (((x) << (n)) | ((x) >> ((sizeof(x) << 3) - (n))))

#define CHX(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define BSIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define BSIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SSIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHFR(x, 3))
#define SSIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10))

#define SHA256_BLOCK_SIZE (512 / 8)
#define SHA256_COVER_SIZE (SHA256_BLOCK_SIZE * 2)

static uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

#if ZDBG
static int zdump_hex(const uint8_t *data, int size) {
    int i;
    int l = 32;

    if (data[0] == 0x21) return 0;

    for (i = 0; i < size; i++) {
        if ((i % l) == 0) {
            printf("[%02x] ", i / l);
        }
        printf("%02x", data[i]);
        if (((i + 1) % l) == 0) {
            printf("\n");
        }
    }

    printf("\n");
    return 0;
}
#else
#define zdump_hex(a, b)
#endif

static int ztransform(const uint8_t *msg, uint32_t *h) {
    uint32_t w[64];
    uint32_t a0, b1, c2, d3, e4, f5, g6, h7;
    uint32_t t1, t2;

    int i = 0;
    int j = 0;

    for (i = 0; i < 16; i++) {
        w[i] = msg[j] << 24 | msg[j + 1] << 16 | msg[j + 2] << 8 | msg[j + 3];
        j += 4;
    }

    for (i = 16; i < 64; i++) {
        w[i] = SSIG1(w[i - 2]) + w[i - 7] + SSIG0(w[i - 15]) + w[i - 16];
    }

    zdump_hex((uint8_t *)w, 64 * 4);

    a0 = h[0];
    b1 = h[1];
    c2 = h[2];
    d3 = h[3];
    e4 = h[4];
    f5 = h[5];
    g6 = h[6];
    h7 = h[7];

    for (i = 0; i < 64; i++) {
        t1 = h7 + BSIG1(e4) + CHX(e4, f5, g6) + k[i] + w[i];
        t2 = BSIG0(a0) + MAJ(a0, b1, c2);

        h7 = g6;
        g6 = f5;
        f5 = e4;
        e4 = d3 + t1;
        d3 = c2;
        c2 = b1;
        b1 = a0;
        a0 = t1 + t2;
    }

    h[0] += a0;
    h[1] += b1;
    h[2] += c2;
    h[3] += d3;
    h[4] += e4;
    h[5] += f5;
    h[6] += g6;
    h[7] += h7;

    return 0;
}

int zsha256(const uint8_t *src, uint32_t len, uint32_t *hash) {
    uint8_t *tmp = (uint8_t *)src;
    uint8_t cover_data[SHA256_COVER_SIZE];
    uint32_t cover_size = 0;

    uint32_t i = 0;
    uint32_t n = 0;
    uint32_t m = 0;
    uint32_t h[8];

    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;

    memset(cover_data, 0x00, sizeof(uint8_t) * SHA256_COVER_SIZE);

    n = len / SHA256_BLOCK_SIZE;
    m = len % SHA256_BLOCK_SIZE;

    if (m < 56) {
        cover_size = SHA256_BLOCK_SIZE;
    } else {
        cover_size = SHA256_BLOCK_SIZE * 2;
    }

    if (m != 0) {
        memcpy(cover_data, tmp + (n * SHA256_BLOCK_SIZE), m);
    }
    cover_data[m] = 0x80;
    cover_data[cover_size - 4] = ((len * 8) & 0xff000000) >> 24;
    cover_data[cover_size - 3] = ((len * 8) & 0x00ff0000) >> 16;
    cover_data[cover_size - 2] = ((len * 8) & 0x0000ff00) >> 8;
    cover_data[cover_size - 1] = ((len * 8) & 0x000000ff);

    zdump_hex(tmp, len - m);
    zdump_hex(cover_data, cover_size);

    for (i = 0; i < n; i++) {
        ztransform(tmp, h);
        tmp += SHA256_BLOCK_SIZE;
    }

    tmp = cover_data;
    n = cover_size / SHA256_BLOCK_SIZE;
    for (i = 0; i < n; i++) {
        ztransform(tmp, h);
        tmp += SHA256_BLOCK_SIZE;
    }

    if (NULL != hash) {
        memcpy(hash, h, sizeof(uint32_t) * 8);
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////
// Reference: https://gist.github.com/creationix/4710780
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint32_t h0, h1, h2, h3;

void md5(uint8_t *initial_msg, size_t initial_len) {
    // Message (to prepare)
    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;

    msg = (uint8_t *)calloc(new_len + 64, 1);  // also appends "0" bits
                                               // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128;  // write the "1" bit

    uint32_t bits_len = 8 * initial_len;  // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);  // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for (offset = 0; offset < new_len; offset += (512 / 8)) {
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *)(msg + offset);

#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);

        int j;
        for (j = 0; j < 64; j++) printf("%x ", ((uint8_t *)w)[j]);
        puts("");
#endif

        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        // Main loop:
        uint32_t i;
        for (i = 0; i < 64; i++) {
#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p = (uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p = (uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p = (uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p = (uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif

            uint32_t f, g;

            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7 * i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
            // printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }

        // Add this chunk's hash to result so far:

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    // cleanup
    free(msg);
}

///////////////////////////////////////////////////////////////////////
uint8_t *create_hash_table(uint8_t **h, uint32_t val) {
    for (int i = 0; i <= 1; ++i) {
        h[i] = (uint8_t *)calloc(val, sizeof(uint8_t));
        if (h[i] == NULL) return NULL;
    }
    return h[0];
}

void free_hash_table(uint8_t **h) {
    for (int i = 0; i <= 1; ++i) {
        free(h[i]);
    }
}

uint32_t sha256(uint32_t val) {
    uint8_t *src;
    uint32_t len;
    uint32_t sha[8];
    uint32_t data[4];
    uint32_t ret;

    data[0] = val;
    data[1] = val ^ 0x12345678;
    data[2] = val ^ 0x13579BDF;
    data[3] = val ^ 0x2468ACE0;

    src = (uint8_t *)data;
    len = strlen((char *)data);
    zsha256(src, len, sha);

    ret = sha[0] ^ sha[1] ^ sha[2] ^ sha[3] ^ sha[4] ^ sha[5] ^ sha[6] ^ sha[7];
    return ret;
}

uint32_t hash_func_sha256(uint32_t val, uint32_t m) {
    uint32_t v = sha256(val);
    return v % m;
}

uint32_t hash_func_md5(uint32_t val, uint32_t m) {
    uint8_t *src;
    uint32_t len;
    uint32_t data[4];

    data[0] = val;
    data[1] = val ^ 0x12345678;
    data[2] = val ^ 0x13579BDF;
    data[3] = val ^ 0x2468ACE0;

    src = (uint8_t *)data;
    len = strlen((char *)data);
    md5(src, len);
    return (h0 ^ h1 ^ h2 ^ h3) % m;
}

int main() {
    uint8_t *hashtable[2];
    uint32_t p, m, n;  // prime number, hash size (bits), # of ids
    uint32_t id, hv, hv2;
    uint8_t bias, bias2;

    scanf("%u %u %u", &p, &m, &n);
    if (create_hash_table(hashtable, (m - 1) / 8 + 1) == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%u", &id);
        hv = hash_func_sha256(id, m);
        bias = hv % 8;
        bias = 1 << bias;
        hv /= 8;
        hv2 = hash_func_md5(id, m);
        bias2 = hv2 % 8;
        bias2 = 1 << bias2;
        hv2 /= 8;
        if ((hashtable[0][hv] & bias) == 0 || (hashtable[1][hv2] & bias2) == 0) {
            hashtable[0][hv] |= bias;
            hashtable[1][hv2] |= bias2;
            printf("%u %u\n", id, 1);
        } else {
            printf("%u %u\n", id, 0);
        }
    }
    free_hash_table(hashtable);
    return 0;
}
