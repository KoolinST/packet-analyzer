#include "PacketSniffer.hpp"
#include "Logger.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <network interface>\n";
        return 1;
    }
    Logger::getInstance().setLogFile("packet_log.txt");

    std::string filterExpression = (argc > 2) ? argv[2] : "";

    PacketSniffer sniffer(argv[1]);
    if (!sniffer.open()) {
        return 1;
    }
    
    if (!filterExpression.empty()) {
        if (!sniffer.setFilter(filterExpression)) {
            std::cerr << "Failed to set BPF filter. Exiting." << std::endl;
            return 1;
        }
    }

    sniffer.start();
    return 0;
}