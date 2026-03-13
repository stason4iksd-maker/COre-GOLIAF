#pragma once

#include <string>

namespace core_goliaf::server {

struct Packet {
    std::string type{"Heartbeat"};
    std::string payload{"{}"};
};

} // namespace core_goliaf::server
