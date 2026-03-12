#include "core/Engine.hpp"

#include <iostream>

int main() {
    Engine engine;
    engine.initialize();

    std::cout << "[LanServer] Listening on UDP port 7777 (stub)" << std::endl;
    std::cout << "[LanServer] Broadcasting discovery packet (stub)" << std::endl;

    engine.update(0.05);
    engine.shutdown();

    return 0;
}
