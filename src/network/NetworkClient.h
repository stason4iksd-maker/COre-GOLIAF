#pragma once
#include <string>

namespace goliaf::network {

class NetworkClient {
public:
    bool Connect(const char* host, int port);
    bool SendJson(const std::string& json);
    std::string Receive();
    void Close();
private:
    int socket_ = -1;
};

}
