#pragma once

namespace core_goliaf::server {

class NetworkServer {
public:
    bool start(const char* host, int port);
    void tick() const;
};

} // namespace core_goliaf::server
