#include "core/Engine.hpp"

#include <iostream>

int main() {
    Engine engine;
    if (!engine.initialize()) {
        std::cerr << "[Player] Engine initialization failed" << std::endl;
        return 1;
    }

    int maxFrames = 300;
    while (engine.isRunning() && maxFrames-- > 0) {
        engine.update(1.0 / 60.0);
        engine.render();
    }

    engine.shutdown();
    std::cout << "[Player] Exit" << std::endl;
    return 0;
}
