#include "PhysicsStub.h"

#include <iostream>

bool PhysicsStub::initialize() {
    std::cout << "[Physics] Physics initialized (stub)." << std::endl;
    return true;
}

void PhysicsStub::update(double dt) const {
    std::cout << "[Physics] Step dt=" << dt << " (stub)." << std::endl;
}
