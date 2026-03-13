#include "network/server.hpp"
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using socket_t = SOCKET;
static constexpr socket_t kInvalidSocket = INVALID_SOCKET;
static void close_socket(socket_t s) { closesocket(s); }
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using socket_t = int;
static constexpr socket_t kInvalidSocket = -1;
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
    std::cout << "LAN server started\n"
              << "[LanServer] name=" << cfg_.name
              << " version=" << cfg_.version
              << " endpoint=" << cfg_.ip << ":" << cfg_.port << "\n";
    tcpThread_ = std::thread(&LanServer::tcpLoop, this);
    udpThread_ = std::thread(&LanServer::udpLoop, this);
    discoveryThread_ = std::thread(&LanServer::discoveryLoop, this);
    return true;
}

void LanServer::tcpLoop() {
    socket_t fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == kInvalidSocket) return;

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&opt), sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(cfg_.port));
    inet_pton(AF_INET, cfg_.ip.c_str(), &addr.sin_addr);

    if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        close_socket(fd);
        return;
    }

    listen(fd, 16);

    while (running_) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd, &set);
        timeval tv{};
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        int ready = select(static_cast<int>(fd + 1), &set, nullptr, nullptr, &tv);
        if (ready > 0 && FD_ISSET(fd, &set)) {
            socket_t c = accept(fd, nullptr, nullptr);
            if (c != kInvalidSocket) {
                std::lock_guard<std::mutex> lock(clientsMutex_);
                clients_.push_back(static_cast<unsigned long long>(c));
                std::cout << "[LanServer] client connected, total=" << clients_.size() << "\n";
            }
        }
    }

    close_socket(fd);
}

void LanServer::udpLoop() {
    while (running_) {
        replicateEntities();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void LanServer::discoveryLoop() {
    socket_t fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == kInvalidSocket) return;

    int enable = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char*>(&enable), sizeof(enable));

    sockaddr_in out{};
    out.sin_family = AF_INET;
    out.sin_port = htons(static_cast<uint16_t>(cfg_.port + 1));
    inet_pton(AF_INET, "255.255.255.255", &out.sin_addr);

    while (running_) {
        std::string announce = "LAN_DISCOVERY " + cfg_.name + " " + cfg_.version + " " + cfg_.ip + ":" + std::to_string(cfg_.port);
        sendto(fd, announce.c_str(), static_cast<int>(announce.size()), 0, reinterpret_cast<sockaddr*>(&out), sizeof(out));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close_socket(fd);
}

void LanServer::replicateEntities() {
    std::lock_guard<std::mutex> lock(clientsMutex_);
    for (auto c : clients_) {
        const char* payload = "replicate entity state";
#ifdef _WIN32
        send(static_cast<SOCKET>(c), payload, static_cast<int>(std::strlen(payload)), 0);
#else
        send(static_cast<int>(c), payload, std::strlen(payload), 0);
#endif
    }
}

void LanServer::stop() {
    running_ = false;
    if (tcpThread_.joinable()) tcpThread_.join();
    if (udpThread_.joinable()) udpThread_.join();
    if (discoveryThread_.joinable()) discoveryThread_.join();

    std::lock_guard<std::mutex> lock(clientsMutex_);
    for (auto c : clients_) {
#ifdef _WIN32
        close_socket(static_cast<SOCKET>(c));
#else
        close_socket(static_cast<int>(c));
#endif
    }
    clients_.clear();

#ifdef _WIN32
    WSACleanup();
#endif
}

}
