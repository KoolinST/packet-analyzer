#include "PacketSniffer.hpp"
#include "PacketParser.hpp"
#include "Logger.hpp"

#include <iostream>
#include <cstring>

PacketSniffer::PacketSniffer(const std::string& interface)
    : interfaceName(interface), handle(nullptr) {}

bool PacketSniffer::open() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    handle = pcap_open_live(interfaceName.c_str(), BUFSIZ, 1, 1000, errorBuffer);
    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errorBuffer << std::endl;
        return false;
    }
    std::cout << "Sniffing on interface: " << interfaceName << std::endl;
    return true;
}


void PacketSniffer::start() {
    if (!handle) {
        std::cerr << "Error: Interface not opened. Call open() first." << std::endl;
        return;
    }

    pcap_loop(handle, 0, packetHandler, nullptr);
    pcap_close(handle);
}

void PacketSniffer::packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    std::string logEntity = PacketParser::parse(packet, *pkthdr);
    std::cout << logEntity << std::endl;
    PacketParser::parse(packet, *pkthdr);
}

bool PacketSniffer::setFilter(const std::string& filterExpression) {
    if (!handle) {
        std::cerr << "Error: Cannot set filter before interface is opened." << std::endl;
        return false;
    }
    
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filterExpression.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) {
        std::cerr << "Failed to compile filter: " << pcap_geterr(handle) << std::endl;
        return false;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        std::cerr << "Failed to set filter: " << pcap_geterr(handle) << std::endl;
        pcap_freecode(&fp);
        return false;
    }
    pcap_freecode(&fp);
    return true;
}