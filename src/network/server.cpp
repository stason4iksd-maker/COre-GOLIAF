#include "network/server.hpp"
#include <chrono>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using socket_t = SOCKET;
static void close_socket(socket_t s) { closesocket(s); }
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using socket_t = int;
static void close_socket(socket_t s) { close(s); }
#endif

namespace network {

bool LanServer::loadConfig(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;
    std::getline(in, cfg_.ip);
    in >> cfg_.port;
    in.ignore();
    std::getline(in, cfg_.name);
    std::getline(in, cfg_.version);
    return true;
}

bool LanServer::start() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    running_ = true;
    tcpThread_ = std::thread(&LanServer::tcpLoop, this);
    udpThread_ = std::thread(&LanServer::udpLoop, this);
    return true;
}

void LanServer::tcpLoop() {
    socket_t fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(cfg_.port));
    inet_pton(AF_INET, cfg_.ip.c_str(), &addr.sin_addr);
    bind(fd, (sockaddr*)&addr, sizeof(addr));
    listen(fd, 8);
    while (running_) {
        socket_t c = accept(fd, nullptr, nullptr);
#ifdef _WIN32
        if (c != INVALID_SOCKET)
#else
        if (c >= 0)
#endif
            clients_.push_back(static_cast<unsigned long long>(c));
    }
    close_socket(fd);
}

void LanServer::udpLoop() {
    socket_t fd = socket(AF_INET, SOCK_DGRAM, 0);
    while (running_) {
        replicateEntities();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    close_socket(fd);
}

void LanServer::replicateEntities() {
    for (auto c : clients_) {
        const char* payload = "replicate entity state";
#ifdef _WIN32
        send(static_cast<SOCKET>(c), payload, 22, 0);
#else
        send(static_cast<int>(c), payload, 22, 0);
#endif
    }
}

void LanServer::stop() {
    running_ = false;
    if (tcpThread_.joinable()) tcpThread_.join();
    if (udpThread_.joinable()) udpThread_.join();
#ifdef _WIN32
    WSACleanup();
#endif
}

}
