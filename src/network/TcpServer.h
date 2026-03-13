#pragma once
#include <atomic>

namespace goliaf::network {

class TcpServer {
public:
    bool Start(const char* host, int port);
    void Stop();
    void RunLoop();
private:
    int listenFd_ = -1;
    std::atomic<bool> running_{false};
};

}
