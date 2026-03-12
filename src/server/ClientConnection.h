#pragma once

#include <string>

namespace core_goliaf::server {

struct ClientConnection {
    int id{0};
    std::string endpoint{"127.0.0.1"};
};

} // namespace core_goliaf::server
