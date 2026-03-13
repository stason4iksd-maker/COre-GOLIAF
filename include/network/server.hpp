#pragma once
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace network {

struct ServerConfig {
    std::string ip{"127.0.0.1"};
    int port{7777};
    std::string name{"LanServer"};
    std::string version{"1.0"};
};

class LanServer {
public:
    bool loadConfig(const std::string& path);
    bool start();
    void stop();
    void replicateEntities();
private:
    void tcpLoop();
    void udpLoop();
    void discoveryLoop();

    ServerConfig cfg_;
    std::atomic<bool> running_{false};
    std::thread tcpThread_;
    std::thread udpThread_;
    std::thread discoveryThread_;
    std::mutex clientsMutex_;
    std::vector<unsigned long long> clients_;
};

}
