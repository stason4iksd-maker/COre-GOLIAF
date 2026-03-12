#include "core/PhysicsSystem.hpp"

#include <iostream>

void PhysicsSystem::initialize() {
    std::cout << "[Physics] System initialized" << std::endl;
}

void PhysicsSystem::step(double deltaTime) const {
    std::cout << "[Physics] Step dt=" << deltaTime << std::endl;
}
