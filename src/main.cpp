#include "PacketSniffer.hpp"
#include "Logger.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <network interface>\n";
        return 1;
    }
    Logger::getInstance().setLogFile("packet_log.txt");

    PacketSniffer sniffer(argv[1]);
    sniffer.start();

    return 0;
}