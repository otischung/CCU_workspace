#include "network.h"

#include "transport.h"

u_char *ipv4_parse(const u_char *start_pos, int len) {
    struct iphdr *iptr;
    uint32_t header_len;
    uint32_t saddr, daddr;
    uint8_t a, b, c, d;

    iptr = (struct iphdr *)start_pos;
    if (iptr->version != IPVERSION) {
        fprintf(stderr, "Error, this is not an IPv4 format.\n");
        return NULL;
    }
    header_len = iptr->ihl << 2;  //ihl = rows of header, each row is 4 bytes.
    if (header_len != sizeof(struct iphdr)) {
        fprintf(stderr, "Error, header length doesn't match");
    }

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

    printf("TTL: %u\n", iptr->ttl);
    printf("Datagram length: %u bytes\n", ntohs(iptr->tot_len));

    switch (iptr->protocol) {
        case IPPROTO_UDP:
            printf("Upper-layer protocol: UDP\n\n");
            udp_parse(start_pos + header_len, len - header_len);
            break;
        case IPPROTO_TCP:
            printf("Upper-layer protocol: TCP\n\n");
            tcp_parse(start_pos + header_len, len - header_len);
            break;
        case IPPROTO_ICMP:
            printf("Upper-layer protocol: ICMP\n\n");
            break;
        case IPPROTO_ICMPV6:
            printf("Upper-layer protocol: ICMPv6\n\n");
            break;
        default:
            printf("Upper-layer protocol: %u\n", iptr->protocol);
            printf("Reference: https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers\n\n");
            break;
    }
}

u_char *ipv6_parse(const u_char *start_pos, int len) {
    struct ip6_hdr *iptr;

    iptr = (struct ip6_hdr *)start_pos;
    printf("Payload length: %u\n", ntohs(iptr->ip6_ctlun.ip6_un1.ip6_un1_plen));
    printf("Hop Limit: %u\n", iptr->ip6_ctlun.ip6_un1.ip6_un1_hlim);
    printf("Source addr: ");
    for (int i = 0; i < 8; ++i) {
        printf("%04x%c", ntohs(iptr->ip6_src.__in6_u.__u6_addr16[i]), ":\n"[i == 7]);
    }
    printf("Destination addr: ");
    for (int i = 0; i < 8; ++i) {
        printf("%04x%c", ntohs(iptr->ip6_dst.__in6_u.__u6_addr16[i]), ":\n"[i == 7]);
    }
    switch (iptr->ip6_ctlun.ip6_un1.ip6_un1_nxt) {
        case IPPROTO_UDP:
            printf("Upper-layer protocol: UDP\n\n");
            udp_parse(start_pos + 40, len - 40);
            break;
        case IPPROTO_TCP:
            printf("Upper-layer protocol: TCP\n\n");
            tcp_parse(start_pos + 40, len - 40);
            break;
        case IPPROTO_ICMP:
            printf("Upper-layer protocol: ICMP\n\n");
            break;
        case IPPROTO_ICMPV6:
            printf("Upper-layer protocol: ICMPv6\n\n");
            break;
        default:
            printf("Upper-layer protocol: %u\n", iptr->ip6_ctlun.ip6_un1.ip6_un1_nxt);
            printf("Reference: https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers\n\n");
            break;
    }
}
