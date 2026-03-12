#include "network/TcpServer.h"

#include "core/Logger.h"

#include <cstring>
#include <string>

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
    if (listen(listenFd_, 8) < 0) return false;

    running_ = true;
    core::Logger::Log("Server", "LAN server started");
    core::Logger::Log("Server", std::string("Listening on ") + host + ":" + std::to_string(port));
    return true;
}

void TcpServer::RunLoop() {
    while (running_) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(listenFd_, &set);
        timeval tv{1,0};
        const int ready = select(listenFd_ + 1, &set, nullptr, nullptr, &tv);
        if (ready <= 0) continue;

        sockaddr_in clientAddr{};
        socklen_t len = sizeof(clientAddr);
        const int client = static_cast<int>(accept(listenFd_, reinterpret_cast<sockaddr*>(&clientAddr), &len));
        if (client < 0) continue;

        char ip[64]{};
        inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));
        core::Logger::Log("Server", std::string("Client connected: ") + ip);

        char buf[1024]{};
        int n = static_cast<int>(recv(client, buf, sizeof(buf)-1, 0));
        if (n > 0) {
            std::string msg(buf, buf + n);
            core::Logger::Log("Server", "Received: " + msg);
            std::string echo = std::string("{\"type\":\"echo\",\"payload\":") + msg + "}";
            send(client, echo.c_str(), static_cast<int>(echo.size()), 0);
        }
        closesock_platform(client);
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
