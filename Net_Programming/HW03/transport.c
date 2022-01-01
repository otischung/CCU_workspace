#include "transport.h"

u_char *udp_parse(const u_char *start_pos, int len) {
    struct udphdr *uptr;

    uptr = (struct udphdr *)start_pos;
    printf("Source port: %u\n", ntohs(uptr->uh_sport));
    printf("Destination port: %u\n", ntohs(uptr->uh_dport));
    printf("Segment length: %u\n", ntohs(uptr->uh_ulen));
}

u_char *tcp_parse(const u_char *start_pos, int len) {
    struct tcphdr *tptr;

    tptr = (struct tcphdr *)start_pos;
    printf("Source port: %u\n", ntohs(tptr->th_sport));
    printf("Destination port: %u\n", ntohs(tptr->th_dport));
    printf("Sequence num: %u\n", ntohl(tptr->th_seq));
    printf("Acknowledgment num: %u\n", ntohl(tptr->th_ack));
    printf("Header length: %u bytes\n", tptr->th_off << 2);

    printf("Flags: ");
    if (tptr->th_flags & TH_FIN) printf("FIN ");
    if (tptr->th_flags & TH_SYN) printf("SYN ");
    if (tptr->th_flags & TH_RST) printf("RST ");
    if (tptr->th_flags & TH_PUSH) printf("PUSH ");
    if (tptr->th_flags & TH_ACK) printf("ACK ");
    if (tptr->th_flags & TH_URG) printf("URG ");
    if (tptr->th_flags & 0x40) printf("ECE ");
    if (tptr->th_flags & 0x80) printf("CWR ");
    putchar('\n');

    // switch (tptr->th_flags) {
    //     case TH_FIN:
    //         printf("Flags: FIN\n");
    //         break;
    //     case TH_SYN:
    //         printf("Flags: SYN\n");
    //         break;
    //     case TH_RST:
    //         printf("Flags: RST\n");
    //         break;
    //     case TH_PUSH:
    //         printf("Flags: PUSH\n");
    //         break;
    //     case TH_ACK:
    //         printf("Flags: ACK\n");
    //         break;
    //     case TH_URG:
    //         printf("Flags: URG\n");
    //         break;
    //     case 0x30:
    //         printf("Flags: ECE\n");
    //         break;
    //     case 0x40:
    //         printf("Flags: CWR\n");
    //         break;
    //     default:
    //         fprintf(stderr, "unknown flags\n");
    //         break;
    // }
}
