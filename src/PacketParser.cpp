#include "PacketParser.hpp"
#include "Logger.hpp"
#include <iostream>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <sstream>


std::string tcpFlagsToString(uint8_t flags) {
    std::ostringstream oss;
    if(flags & TH_FIN) oss << "FIN ";
    if(flags & TH_SYN) oss << "SYN ";
    if(flags & TH_RST) oss << "RST ";
    if(flags & TH_PUSH) oss << "PSH ";
    if(flags & TH_ACK) oss << "ACK ";
    if(flags & TH_URG) oss << "URG ";
    std::string result = oss.str();
    if(result.empty()) return "No Flags";
    result.pop_back();
    return result;
}

std::string PacketParser::parse(const u_char* packet, const struct pcap_pkthdr& packetHeader){
    std::ostringstream oss;
    const struct ether_header* ethHeader = (struct ether_header*) packet;

    if(ntohs(ethHeader -> ether_type) == ETHERTYPE_IP) {
        const struct ip* ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
        std::string srcIP = inet_ntoa(ipHeader -> ip_src);
        std::string dstIP = inet_ntoa(ipHeader -> ip_dst);

        oss << "IP Packet: " << srcIP << " -> " << dstIP << " ";

        if(ipHeader -> ip_p == IPPROTO_TCP){
            const struct tcphdr* tcpHeader = (struct tcphdr*)(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            uint16_t srcPort = ntohs(tcpHeader->th_sport);
            uint16_t dstPort = ntohs(tcpHeader->th_dport);
            std::string flags = tcpFlagsToString(tcpHeader->th_flags);
            oss << "\tTCP " << srcPort << " -> " << dstPort << " Flags: " << flags;
        }
        else if (ipHeader->ip_p == IPPROTO_UDP) {
            const struct udphdr* udpHeader = (struct udphdr*)(packet + sizeof(struct ether_header) + ipHeader->ip_hl * 4);
            oss << "\tUDP: " << ntohs(udpHeader->uh_sport) << " -> " << ntohs(udpHeader->uh_dport);
        }
        else{
            oss << "Other IP Protocol: " << (int)ipHeader->ip_p;
        }
    }
    else{
        oss << "Non-IP packet";
    }
    oss << " [Size: " << packetHeader.len << " bytes]";
    std::string finalLog = oss.str();
    Logger::getInstance().log(finalLog);

    return finalLog;
}

