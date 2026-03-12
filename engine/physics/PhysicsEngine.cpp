#include "physics/PhysicsEngine.h"

#include "core/Logger.h"

namespace core_goliaf::physics {

bool PhysicsEngine::initialize() {
    core::Logger::info("Physics", "Initialized");
    core::Logger::info("Engine", "Physics initialized");
    return true;
}

void PhysicsEngine::update(double deltaTime) const {
    core::Logger::info("Physics", "Update dt=" + std::to_string(deltaTime));
}

} // namespace core_goliaf::physics
