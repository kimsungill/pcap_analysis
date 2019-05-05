#include <stdio.h>
#include <stdint.h>

struct ethheader {
    uint8_t e_mac[12];
    uint16_t e_type;
};

struct ipheader {
    uint8_t ip_vlen;
    uint8_t ip_tos;
    uint16_t ip_tlen;
    uint16_t ip_id;
    uint8_t ip_flags;
    uint8_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_pro;
    uint16_t ip_check;
    uint8_t ip_add[8];

};

struct tcpheader {
    uint16_t t_port[2];
    uint32_t t_seq;
    uint32_t t_ack;
    uint8_t t_off;
    uint8_t t_flags;
    uint16_t t_win;
    uint16_t t_csum;
    uint16_t t_pt;
};

struct httpheader {
    uint8_t h_data[16];
};

void home(const unsigned char *data);
