#include "PacketSniffer.hpp"
#include "PacketParser.hpp"

#include <iostream>
#include <cstring>

PacketSniffer::PacketSniffer(const std::string& interface)
    : interfaceName(interface), handle(nullptr) {}

void PacketSniffer::start() {
    char errorBuffer[PCAP_ERRBUF_SIZE];

    handle = pcap_open_live(interfaceName.c_str(), BUFSIZ, 1, 1000, errorBuffer);
    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errorBuffer << std::endl;
        return;
    }

    std::cout << "Sniffing on interface: " << interfaceName << std::endl;

    pcap_loop(handle, 0, packetHandler, nullptr);

    pcap_close(handle);
}

void PacketSniffer::packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    PacketParser::parse(packet, *pkthdr);
}
