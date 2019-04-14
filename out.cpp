#include "out.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <netinet/ip.h>

void home (const uint8_t *data){
    int ethlen = sizeof(ethheader);
    struct ethheader *ethprint = (struct ethheader *)data;
    struct ipheader *ipprint = (struct ipheader *)(data+ethlen);
    uint8_t iphlen = ((ipprint->verlen) & 0x0F) * 4;
    struct tcpheader *tcpprint = (struct tcpheader *)(data+ethlen+iphlen);
    uint8_t tcphlen = ((tcpprint->offset) >> 4) * 4;
    uint16_t httplen = ntohs(ipprint->tlan) - tcphlen - iphlen;
    struct httpheader *httpprint = (struct httpheader *)(data+ethlen+iphlen+tcphlen);

    printf("------------------------------\n");
    printf("DMAC = ");
    for(int i = 0; i < 6; i++){
    printf("%02X",ethprint->mac[i]);
    if(i < 5)
        printf(":");
    }

    printf("\nSMAC = ");
    for(int i = 6; i < 12; i++){
    printf("%02X",ethprint->mac[i]);
    if(i < 11)
        printf(":");
    }

    if (ntohs(ethprint->type) == 0x0800 ){
    printf("\nSIP = ");
    for (int i = 0; i < 4; i++){
        printf("%u",ipprint->address[i]);
        if(i < 3)
            printf(".");
    }

    printf("\nDIP = ");
    for (int i = 4; i < 8; i++){
        printf("%u",ipprint->address[i]);
        if(i < 7)
            printf(".");
    }

    if (ipprint->protocol == 6){
    printf("\nSPORT = %u",ntohs(tcpprint->port[0]));
    printf("\nDPORT = %u",ntohs(tcpprint->port[1]));

    if (httplen > 16){
    printf("\nHTTP DATA = ");
    for(int z = 0; z < 16; z++){
    printf("%c",httpprint->httpdata[z]);
    }
    } else {
        printf("\nHTTP DATA ERROR!");
    }
    }

    printf("------------------------------\n");
    }

    printf("\n");

}
