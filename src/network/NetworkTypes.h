#pragma once
#include <string>

namespace goliaf::network {
struct Packet {
    std::string type;
    std::string payload;
};
}
