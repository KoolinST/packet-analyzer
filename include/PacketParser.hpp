#ifndef PACKET_PARSER_HPP
#define PACKET_PARSER_HPP

#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>

class PacketParser {
    public:
        static void parse(const u_char* packet, const struct pcap_pkthdr& packetHeader);
};

#endif
