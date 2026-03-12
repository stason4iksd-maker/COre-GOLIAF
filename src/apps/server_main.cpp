#include "network/TcpServer.h"

int main() {
    goliaf::network::TcpServer server;
    if (!server.Start("127.0.0.1", 12345)) {
        return 1;
    }
    server.RunLoop();
    server.Stop();
    return 0;
}
