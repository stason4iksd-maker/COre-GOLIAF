#include "core/Engine.hpp"

#include <iostream>

int main() {
    Engine engine;
    if (!engine.initialize()) {
        std::cerr << "[Dev] Engine initialization failed" << std::endl;
        return 1;
    }

    int maxFrames = 120;
    while (engine.isRunning() && maxFrames-- > 0) {
        engine.update(1.0 / 60.0);
        engine.render();
    }

    engine.shutdown();
    std::cout << "[Dev] Completed run" << std::endl;
    return 0;
}
