// Reference: https://www.tcpdump.org/pcap.html
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/in_systm.h> /* required for ip.h */
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int ret;

    memset(errbuf, '\0', PCAP_ERRBUF_SIZE * sizeof(char));
    filter_exp = strdup("port 53 or port 80 or port 443");
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

    /* Grab a packet */
    packet = pcap_next(handle, &header);  // packet = the start pos. of the packet
    /* Print its length */
    printf("Jacked a packet with\n");
    printf("Length of this packet: %u\n", header.len);
    printf("Length of portion present: %u\n", header.caplen);
    printf("Time: %u\n\n", header.ts.tv_sec * 1000000 + header.ts.tv_usec);

    eptr = (struct ether_header *)packet;
    if (ntohs(eptr->ether_type) == ETHERTYPE_IP) {
        printf("Ethertype: IPv4\n");
    } else if (ntohs(eptr->ether_type) == ETHERTYPE_IPV6) {
        printf("Ethertype: IPv6\n");
    } else if (ntohs(eptr->ether_type) == ETHERTYPE_ARP) {
        printf("Ethertype: ARP\n");
    } else if (ntohs(eptr->ether_type) == ETHERTYPE_REVARP) {
        printf("Ethertype: RARP\n");
    } else {
        fprintf(stderr, "WTF\n");
    }
    /* And close the session */
    pcap_close(handle);

    // ret = pcap_loop(handle, 1, got_packet, NULL);

    return EXIT_SUCCESS;
}
