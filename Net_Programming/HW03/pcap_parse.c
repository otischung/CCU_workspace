// Reference: https://www.tcpdump.org/pcap.html
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv) {
    // pcap_if_t *alldevs;
    pcap_t *readpcap;
    struct bpf_program fp;
    char errbuf[PCAP_ERRBUF_SIZE];  // PCAP_ERRBUF_SIZE = 256
    char filter_exp[] = "port 53";	/* The filter expression */
    struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet;		/* The actual packet */
    int ret;

    memset(errbuf, '\0', PCAP_ERRBUF_SIZE * sizeof(char));
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
    
    readpcap = pcap_open_offline(argv[1], errbuf);
    if (readpcap == NULL) {
        fprintf(stderr, "Couldn't open file %s: %s\n", argv[1], errbuf);
        return EXIT_FAILURE;
    }
    ret = pcap_compile(readpcap, &fp, filter_exp, 1, 0);
    if (ret == PCAP_ERROR) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(readpcap));
        return EXIT_FAILURE;
    }
    ret = pcap_setfilter(readpcap, &fp);
    if (ret == PCAP_ERROR) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(readpcap));
        return EXIT_FAILURE;
    }

    /* Grab a packet */
	packet = pcap_next(readpcap, &header);
	/* Print its length */
	printf("Jacked a packet with length of [%d]\n", header.len);
	/* And close the session */
	pcap_close(readpcap);



    return EXIT_SUCCESS;
}
