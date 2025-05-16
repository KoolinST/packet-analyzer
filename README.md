# Packet Analyzer in C++

A simple real-time network packet analyzer built in C++ using **libpcap**.

## Features (so far)
- Captures packets using `libpcap`
- Cross-platform build system using CMake
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

# Enjoy using it