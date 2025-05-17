// #ifndef PACKET_CAPTURE_HPP
// #define PACKET_CAPTURE_HPP

// #include <pcap.h>
// #include <string>

// class PacketCapture{
//     public:
//         explicit PacketCapture(const std::string& interface);
//         ~PacketCapture();

//         void startCapture();
//     private:
//         pcap_t* handle;
//         char errbuf[PCAP_ERRBUF_SIZE];
//         std::string interfaceName;

//         static void packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
// };

// #endif