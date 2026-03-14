#include "core/Engine.hpp"

#include <iostream>

int main() {
    Engine engine;
    if (!engine.initialize()) {
        std::cerr << "[LanServer] Engine initialization failed" << std::endl;
        return 1;
    }

    int ticks = 200;
    while (engine.isRunning() && ticks-- > 0) {
        engine.update(0.05);
    }

    engine.shutdown();
    std::cout << "[LanServer] Stopped" << std::endl;
    return 0;
}
