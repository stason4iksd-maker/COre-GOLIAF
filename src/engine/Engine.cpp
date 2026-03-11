#include "core/Engine.hpp"

#include <iostream>

void Engine::initialize() {
    initialized_ = true;
    std::cout << "[Engine] Initialized" << std::endl;
}

void Engine::update(double deltaTime) {
    if (!initialized_) {
        std::cout << "[Engine] Skipped update (not initialized)" << std::endl;
        return;
    }

    std::cout << "[Engine] Updating frame, dt=" << deltaTime << std::endl;
}

void Engine::shutdown() {
    initialized_ = false;
    std::cout << "[Engine] Shutdown" << std::endl;
}
