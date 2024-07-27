#define MAC_ADDRESS_LEN 6
typedef struct Ethernet{
    unsigned char des_add[MAC_ADDRESS_LEN]; //need
    unsigned char src_add[MAC_ADDRESS_LEN]; //need
    unsigned char type[2];
};

//src_ip, dst_ip
typedef struct IP{
    unsigned char ver;
    unsigned char dcsp;
    unsigned char total_len[2];
    unsigned char identification[2];
    unsigned char fragment_offset[2];
    unsigned char ttl[2];
    unsigned char protocol[2];
    //unsigned char header_checksum;
    unsigned char src_add[4];
    unsigned char des_add[4];
};

//src port,dst port
typedef struct TCP{
    unsigned char src_add[2];
    unsigned char des_add[2];
    unsigned char others[16];
    unsigned char payload[4];
};

//payload(data) maximal : 20byte

