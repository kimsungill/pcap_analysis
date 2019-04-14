#include <stdio.h>
#include <stdint.h>

struct ethheader {
    uint8_t mac[12];
    uint16_t type;
};

struct ipheader {
    uint8_t verlen;
    uint8_t typeofse;
    uint16_t tlan;
    uint16_t iden;
    uint8_t flags;
    uint8_t offset;
    uint8_t TTL;
    uint8_t protocol;
    uint16_t check;
    uint8_t address[8];
};

struct tcpheader {
    uint16_t port[2];
    uint32_t sqnumber;
    uint32_t acknumber;
    uint8_t offset;
    uint8_t flag;
    uint16_t winsize;
    uint16_t checksum;
    uint16_t pointer;
};

struct httpheader {
    uint8_t httpdata[16];
};

void home(const uint8_t *data);
