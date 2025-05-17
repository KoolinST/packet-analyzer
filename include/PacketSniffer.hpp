#ifndef PACKET_SNIFFER_HPP
#define PACKET_SNIFFER_HPP

#include <pcap.h>
#include <string>

class PacketSniffer {
public:
    explicit PacketSniffer(const std::string& interface);
    void start();

private:
    std::string interfaceName;
    pcap_t* handle;

    static void packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
};

#endif
