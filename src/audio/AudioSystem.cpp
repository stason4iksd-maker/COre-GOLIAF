#include "core/AudioSystem.hpp"

#include <iostream>

void AudioSystem::initialize() {
    std::cout << "[Audio] System initialized" << std::endl;
}

void AudioSystem::update() const {
    std::cout << "[Audio] Update" << std::endl;
}
