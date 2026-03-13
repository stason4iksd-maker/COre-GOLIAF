#include "network/server.hpp"
#include <chrono>
#include <thread>

int main() {
    network::LanServer server;
    if (!server.loadConfig("config/server.txt")) return 1;
    if (!server.start()) return 1;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    server.stop();
    return 0;
}
