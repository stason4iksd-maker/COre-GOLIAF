#include "core/EcsWorld.hpp"

#include <iostream>

void EcsWorld::initialize() {
    std::cout << "[ECS] World initialized" << std::endl;
}

void EcsWorld::tick(double deltaTime) const {
    std::cout << "[ECS] Tick dt=" << deltaTime << std::endl;
}
