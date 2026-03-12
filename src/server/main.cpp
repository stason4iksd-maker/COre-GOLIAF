#include "server/NetworkServer.h"

int main() {
    core_goliaf::server::NetworkServer server;
    server.start("127.0.0.1", 12345);
    server.tick();
    return 0;
}
