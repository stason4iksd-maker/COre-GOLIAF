#include "network/TcpServer.h"

#include "core/Logger.h"
#include <nlohmann/json.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using socklen_t = int;
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace goliaf::network {

static void closesock_platform(int s) {
#ifdef _WIN32
    closesocket(s);
#else
    close(s);
#endif
}

bool TcpServer::Start(const char* host, int port) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    listenFd_ = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
    if (listenFd_ < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(port));
    inet_pton(AF_INET, host, &addr.sin_addr);

    int opt = 1;
    setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt));
    if (bind(listenFd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) return false;
    if (listen(listenFd_, 32) < 0) return false;

    running_ = true;
    core::Logger::Log("Server", "LAN server started");
    core::Logger::Log("Server", std::string("Listening on ") + host + ":" + std::to_string(port));
    return true;
}

void TcpServer::RunLoop() {
    std::vector<int> clients;
    std::unordered_map<int, nlohmann::json> playerState;

    while (running_) {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(listenFd_, &readSet);
        int maxFd = listenFd_;
        for (int c : clients) {
            FD_SET(c, &readSet);
            if (c > maxFd) maxFd = c;
        }

        timeval tv{0, 100000};
        int ready = select(maxFd + 1, &readSet, nullptr, nullptr, &tv);
        if (ready < 0) continue;

        if (FD_ISSET(listenFd_, &readSet)) {
            sockaddr_in ca{};
            socklen_t len = sizeof(ca);
            int c = static_cast<int>(accept(listenFd_, reinterpret_cast<sockaddr*>(&ca), &len));
            if (c >= 0) {
                clients.push_back(c);
                char ip[64]{};
                inet_ntop(AF_INET, &ca.sin_addr, ip, sizeof(ip));
                core::Logger::Log("Server", std::string("Client connected: ") + ip);
            }
        }

        for (auto it = clients.begin(); it != clients.end();) {
            int c = *it;
            if (!FD_ISSET(c, &readSet)) { ++it; continue; }

            char buf[2048]{};
            int n = static_cast<int>(recv(c, buf, sizeof(buf)-1, 0));
            if (n <= 0) {
                closesock_platform(c);
                it = clients.erase(it);
                continue;
            }

            std::string msg(buf, buf+n);
            try {
                auto j = nlohmann::json::parse(msg);
                if (j.value("type", "") == "position") {
                    playerState[c] = j["payload"];
                }
                nlohmann::json snap;
                snap["type"] = "snapshot";
                snap["players"] = nlohmann::json::array();
                for (auto& kv : playerState) snap["players"].push_back(kv.second);
                const std::string out = snap.dump();
                send(c, out.c_str(), static_cast<int>(out.size()), 0);
                core::Logger::Log("Server", "Syncing entities");
            } catch (...) {
                const std::string out = std::string("{\"type\":\"echo\",\"payload\":") + msg + "}";
                send(c, out.c_str(), static_cast<int>(out.size()), 0);
            }
            ++it;
        }
    }
}

void TcpServer::Stop() {
    running_ = false;
    if (listenFd_ >= 0) {
        closesock_platform(listenFd_);
        listenFd_ = -1;
    }
#ifdef _WIN32
    WSACleanup();
#endif
}

}
