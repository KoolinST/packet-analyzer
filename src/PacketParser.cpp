#include "PacketParser.hpp"
#include <iostream>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

void PacketParser::parse(const u_char* packet, const struct pcap_pkthdr& packetHeader){
    const struct ether_header* ethHeader = (struct ether_header*) packet;

    if(ntohs(ethHeader -> ether_type) == ETHERTYPE_IP) {
        const struct ip* ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
        std::string srcIP = inet_ntoa(ipHeader -> ip_src);
        std::string dstIP = inet_ntoa(ipHeader -> ip_dst);

        std::cout << "IP Packet: " << srcIP << " -> " << dstIP << std::endl;

        if(ipHeader -> ip_p == IPPROTO_TCP){
            const struct tcphdr* tcpHeader = (struct tcphdr*)(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            std::cout << "TCP: " << ntohs(tcpHeader->th_sport) << " -> " << ntohs(tcpHeader->th_dport) << std::endl;
        }
        else if (ipHeader->ip_p == IPPROTO_UDP) {
            const struct udphdr* udpHeader = (struct udphdr*)(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            std::cout << "UDP: " << ntohs(udpHeader->uh_sport) << " -> " << ntohs(udpHeader->uh_dport) << std::endl;
        }
        else{
            std::cout << "Other IP Protocol: " << (int)ipHeader->ip_p << std::endl;
        }
    }
    else{
        std::cout << "Non-IP packet" << std::endl;
    }
    std::cout << std::dec << "\n----------------\n";
}

