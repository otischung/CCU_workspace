// Reference: https://www.tcpdump.org/pcap.html
#include "headers.h"
#include "network.h"

void got_packet(u_char *argv, const struct pcap_pkthdr *header, const u_char *packet) {
}

int main(int argc, char **argv) {
    // pcap_if_t *alldevs;
    pcap_t *handle;                /* Session handle */
    struct bpf_program fp;         /* The compiled filter expression */
    char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */
    char *filter_exp;              /* The filter expression */
    struct pcap_pkthdr header;     /* The header that "pcap gives us", not the packet itself*/
    const u_char *packet;          /* The actual packet */
    bpf_u_int32 mask;              /* The netmask of our sniffing device */
    bpf_u_int32 net;               /* The IP of our sniffing device */
    int optimize;                  /* The optimize flag while compiling.*/
    struct ether_header *eptr;
    int packet_cnt;

    int ret;

    memset(errbuf, '\0', PCAP_ERRBUF_SIZE * sizeof(char));
    filter_exp = strdup("");
    optimize = 1;
    mask = 0;
    // Find all usable network devices.
    // ret = pcap_findalldevs(&alldevs, errbuf);
    // if (ret < 0) {
    //     fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
    //     return EXIT_FAILURE;
    // }

    // // pcap_if_t is a linked-list structure.
    // for (pcap_if_t *d = alldevs; d != NULL; d = d->next) {
    //     printf("Name: %s,\tDescription: %s,\tflags: %u\n", d->name, d->description, d->flags);
    // }
    // printf("\nError buffer: %s\n\n", errbuf);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename or - for stdin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle = pcap_open_offline(argv[1], errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open file %s: %s\n", argv[1], errbuf);
        return EXIT_FAILURE;
    }
    ret = pcap_compile(handle, &fp, filter_exp, optimize, mask);  // enable optmization by setting flag = 1
    if (ret == PCAP_ERROR) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return EXIT_FAILURE;
    }
    ret = pcap_setfilter(handle, &fp);
    if (ret == PCAP_ERROR) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return EXIT_FAILURE;
    }

    packet_cnt = 0;
    /* Grab a packet */
    while ((packet = pcap_next(handle, &header)) != NULL) {  // packet = the start pos. of the packet
        /* Print its length */
        printf("-------------------------------------------\n");
        printf("Packet No.%d\n", ++packet_cnt);
        printf("Length of this packet: %u\n", header.len);
        printf("Length of portion present: %u\n", header.caplen);
        printf("Time stamp: %u\n\n", header.ts.tv_sec * 1000000 + header.ts.tv_usec);

        eptr = (struct ether_header *)packet;
        printf("Destination MAC addr: ");
        for (int i = 0; i < 6; ++i) {
            printf("%02x%c", eptr->ether_dhost[i], ":\n"[i == 5]);
        }
        printf("Source MAC addr: ");
        for (int i = 0; i < 6; ++i) {
            printf("%02x%c", eptr->ether_shost[i], ":\n"[i == 5]);
        }
        switch (ntohs(eptr->ether_type)) {
            case ETHERTYPE_IP:
                printf("Ethertype: IPv4\n\n");
                ipv4_parse(packet + 14, header.len - 14);  // MAC: 6 bytes, Type: 2 bytes
                break;
            case ETHERTYPE_IPV6:
                printf("Ethertype: IPv6\n\n");
                ipv6_parse(packet + 14, header.len - 14);
                break;
            case ETHERTYPE_IPX:
                printf("Ethertype: IPX\n\n");
                break;
            case ETHERTYPE_ARP:
                printf("Ethertype: ARP\n\n");
                break;
            case ETHERTYPE_REVARP:
                printf("Ethertype: RARP\n\n");
                break;
            case 0x0842:
                printf("Ethertype: WoL\n\n");
                break;
            default:
                printf("Ethertype: %04x\n", eptr->ether_type);
                printf("Reference: https://en.wikipedia.org/wiki/EtherType\n\n");
                break;
        }
        printf("-------------------------------------------\n");
    }
    /* And close the session */
    pcap_close(handle);
    // ret = pcap_loop(handle, 1, got_packet, NULL);
    return EXIT_SUCCESS;
}
