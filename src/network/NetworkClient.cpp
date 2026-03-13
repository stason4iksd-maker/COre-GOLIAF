#include "network/NetworkClient.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace goliaf::network {

bool NetworkClient::Connect(const char* host, int port) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    socket_ = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
    if (socket_ < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(port));
    inet_pton(AF_INET, host, &addr.sin_addr);
    return connect(socket_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0;
}

bool NetworkClient::SendJson(const std::string& json) {
    if (socket_ < 0) return false;
    return send(socket_, json.c_str(), static_cast<int>(json.size()), 0) > 0;
}

std::string NetworkClient::Receive() {
    if (socket_ < 0) return {};
    char b[1024]{};
    int n = static_cast<int>(recv(socket_, b, sizeof(b)-1, 0));
    if (n <= 0) return {};
    return std::string(b, b+n);
}

void NetworkClient::Close() {
    if (socket_ >= 0) {
#ifdef _WIN32
        closesocket(socket_);
        WSACleanup();
#else
        close(socket_);
#endif
        socket_ = -1;
    }
}

}
