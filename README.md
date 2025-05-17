# Packet Analyzer in C++

A simple real-time network packet analyzer built in C++ using **libpcap**.

## Features (so far)
- Captures packets using `libpcap`
- Parses Ethernet, IP, TCP, and UDP headers
- Cross-platform build system using CMake
- Clean separation into:
  - `PacketCapture` – handles low-level capture loop in saved directory
  - `PacketParser` – decodes packet contents
  - `PacketSniffer` – integrates parser with capture logic
- Command-line usage: `sudo ./PacketAnalyzer <interface>`
- Replace <interface> with your actual network interface name.


## Build Instructions
If not executed yet
```bash
export PKG_CONFIG_PATH="/opt/homebrew/opt/libpcap/lib/pkgconfig"
export LDFLAGS="-L/opt/homebrew/opt/libpcap/lib"
export CPPFLAGS="-I/opt/homebrew/opt/libpcap/include"
```

```bash
mkdir build && cd build
cmake ..
make
```
## Dependencies
- libpcap
- C++17+
- cmake 4.0.2+
# Enjoy using it