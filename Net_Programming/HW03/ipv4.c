#include "ipv4.h"

u_char *ipv4_parse(const u_char *start_pos, int len) {
    struct iphdr *iptr;
    uint32_t saddr, daddr;
    uint8_t a, b, c, d;

    iptr = (struct iphdr *)start_pos;
    saddr = ntohl(iptr->saddr);
    d = saddr % 256;
    saddr /= 256;
    c = saddr % 256;
    saddr /= 256;
    b = saddr % 256;
    saddr /= 256;
    a = saddr;
    printf("Source addr: %u.%u.%u.%u\n", a, b, c, d);
    daddr = ntohl(iptr->daddr);
    d = daddr % 256;
    daddr /= 256;
    c = daddr % 256;
    daddr /= 256;
    b = daddr % 256;
    daddr /= 256;
    a = daddr;
    printf("Destination addr: %u.%u.%u.%u\n", a, b, c, d);
}
