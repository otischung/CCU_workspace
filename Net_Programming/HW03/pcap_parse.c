#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    // pcap_if_t *alldevs;
    pcap_t *readpcap;
    char errbuf[PCAP_ERRBUF_SIZE];  // PCAP_ERRBUF_SIZE = 256
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
        fprintf(stderr, "%s\n", errbuf);
    }
    



    return EXIT_SUCCESS;
}
