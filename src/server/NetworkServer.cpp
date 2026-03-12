#include "server/NetworkServer.h"

#include "core/Logger.h"

namespace core_goliaf::server {

bool NetworkServer::start(const char* host, int port) {
    core::Logger::info("Server", "LAN server started");
    core::Logger::info("Server", "Listening on " + std::string(host) + ":" + std::to_string(port));
    core::Logger::info("Server", "Replication/synchronization hooks ready (stub)");
    return true;
}

void NetworkServer::tick() const {
    core::Logger::info("Server", "Server tick (stub)");
}

} // namespace core_goliaf::server
