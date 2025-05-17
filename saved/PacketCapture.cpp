// #include "PacketCapture.hpp"
// #include <iostream>
// #include <iomanip>

// PacketCapture::PacketCapture(const std::string& interface) : interfaceName(interface), handle(nullptr) {
//     handle = pcap_open_live(interfaceName.c_str(), BUFSIZ, 1, 1000, errbuf);
//     if(handle == nullptr)
//         throw std::runtime_error("Could not open device: " + interfaceName + " - " + std::string(errbuf));
// }

// PacketCapture::~PacketCapture(){
//     if(handle)
//         pcap_close(handle);
// }

// void PacketCapture::startCapture(){
//     std::cout << "[*] Starting capture on interface: " << interfaceName << "\n";
//     pcap_loop(handle, 0, packetHandler, nullptr);
// }

// void PacketCapture::packetHandler(u_char* userData, const struct pcap_pkthdr* header, const u_char* packet){
//     std::cout << "[+] Packet captured - Length " << header->len << " bytes\n";

//     for(int i = 0; i < header->len; ++i){
//         std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)packet[i] << " ";
//         if ((i + 1) % 16 == 0) std::cout << "\n";
//     }
//     std::cout << std::dec << "\n----------------\n";
// }
