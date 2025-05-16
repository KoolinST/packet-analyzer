#include "PacketCapture.hpp"
#include <iostream>

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << "<network interface>\n";
        return 1;
    }

    try {
        PacketCapture capturer(argv[1]);
        capturer.startCapture();
    }
    catch(const std::exception& ex) {
        std::cerr << "[ERROR]" << ex.what() << "\n";
        return 1;
    }

    return 0;
}