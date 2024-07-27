#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include "pcap-test.h"

void usage() {
	printf("syntax: pcap-test <interface>\n");
	printf("sample: pcap-test wlan0\n");
}

typedef struct {
	char* dev_;
} Param;

Param param = {
	.dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
	if (argc != 2) {
		usage();
		return false;
	}
	param->dev_ = argv[1];
	return true;
}

int main(int argc, char* argv[]) {
	if (!parse(&param, argc, argv))
		return -1;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
	if (pcap == NULL) {
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
		return -1;
	}

	while (true) {
		struct pcap_pkthdr* header;
		const u_char* packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == 0) continue;
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}
		printf("%u bytes captured\n", header->caplen);

		struct Ethernet *Eth = (struct Ethernet *)packet;
		struct IP *Ip = (struct IP*)(packet + sizeof(struct Ethernet));
		struct TCP *Tcp = (struct TCP *)(packet + sizeof(struct Ethernet) + sizeof(struct IP));

		printf("Ethernet des address : ");
		for(int i = 0 ; i < MAC_ADDRESS_LEN; i++){
			printf("%02x", Eth->des_add[i]);
			if(i < MAC_ADDRESS_LEN - 1){
				printf(":");
			}
		}

		printf("\nEthernet src address : ");
		for(int i = 0 ; i < MAC_ADDRESS_LEN ; i++){
			printf("%02x", Eth->src_add[i]);
			if(i < MAC_ADDRESS_LEN - 1){
				printf(":");
			}
		}

		printf("\nIP src address : ");
		for(int i = 0 ; i < 4; i++){
			printf("%02x", Ip -> src_add[i]);
			if(i < 2){
				printf(":");
			}
		}

		printf("\nIP des address : ");
		for(int i = 0 ; i < 4 ; i++){
			printf("%02x", Ip -> des_add[i]);
			if(i < 3){
				printf(":");
			}
		}

		printf("\nTCP src address : ");
		for(int i = 0 ; i < 2; i++){
			printf("%02x", Tcp->src_add[i]);
			if(i == 0){
				printf(":");
			}
		}

		printf("\nTCP des address : ");
		for(int i = 0 ; i < 2; i++){
			printf("%02x", Tcp->des_add[i]);
			if(i == 0){
				printf(":");
			}
		}

		printf("\nTCP PayLoad : ");
		for(int i = 0 ; i < 4 ; i++){
			printf("%02x", Tcp->payload[i]);
			if(i < 3){
				printf(":");
			}
		}
		printf("\n");
	}

	pcap_close(pcap);
}