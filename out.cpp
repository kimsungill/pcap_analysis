#include "out.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <netinet/ip.h>
#include <stdlib.h>

void home (const unsigned char *data){
    int ethlen = sizeof(ethheader);
    struct ethheader *ethprint = (struct ethheader *)data;
    data = (data+ethlen);
    struct ipheader *ipprint = (struct ipheader *)data;
    uint8_t iphlen = ((ipprint->ip_vlen) & 0x0F) * 4;
    data = (data+iphlen);
    struct tcpheader *tcpprint = (struct tcpheader *)data;
    uint8_t tcphlen = ((tcpprint->t_off) >> 4) * 4;
    uint16_t httplen = ntohs(ipprint->ip_tlen) - tcphlen - iphlen;
    data = (data+tcphlen);
    struct httpheader *httpprint = (struct httpheader *)data;

    printf("------------------------------------ETHERNET Header");
    for(int i = 0; i < 12; i++){
        if(i < 6){
            if (i == 0){
                printf("\nDMAC = ");
            }
            printf("%02X",ethprint->e_mac[i]);
            if(i < 5)
                printf(":");
        }

        if(i > 5){
            if(i == 6){
                printf("\nSMAC = ");
            }
            printf("%02X",ethprint->e_mac[i]);
            if(i < 11)
                printf(":");
        }
    }

    if (ntohs(ethprint->e_type) == 0x0800 ){
        printf("\n------------------------------------IP Header");
        for (int i = 0; i < 8; i++){
            if(i < 4){
                if(i == 0){
                    printf("\nSIP = ");
                }
                printf("%u",ipprint->ip_add[i]);
                if(i < 3)
                    printf(".");
            }
            if(i > 3){
                if(i == 4){
                    printf("\nDIP = ");
                }
                printf("%u",ipprint->ip_add[i]);
                if(i < 7)
                    printf(".");
            }
        }

        if (ipprint->ip_pro == 6){
            printf("\n------------------------------------TCP Header");
            printf("\nSPORT = %u",ntohs(tcpprint->t_port[0]));
            printf("\nDPORT = %u",ntohs(tcpprint->t_port[1]));

            printf("\n------------------------------------HTTP Header");
            if (httplen > 16){
                printf("\nHTTP DATA = ");
                for(int z = 0; z < 16; z++){
                    printf("%c",httpprint->h_data[z]);
                }
            } else {
                printf("\nHTTP DATA = ");
                for(int z = 0; z < httplen; z++){
                    printf("%c",httpprint->h_data[z]);
                }
            }
        }
    }
    printf("\n");
}
