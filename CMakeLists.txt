cmake_minimum_required(VERSION 4.0.2)

project(PacketAnalyzer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

include_directories(${PCAP_INCLUDE_DIRS})
link_directories(${PCAP_LIBRARY_DIRS})

add_executable(PacketAnalyzer
    src/main.cpp
    src/PacketParser.cpp
    src/PacketSniffer.cpp
    src/Logger.cpp
)

target_include_directories(PacketAnalyzer PRIVATE include)
target_link_libraries(PacketAnalyzer pcap)