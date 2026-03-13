#include "PhysicsSystem.h"

#include <algorithm>

namespace goliaf {

bool PhysicsSystem::intersects(const AABB& lhs, const AABB& rhs) {
    return lhs.minX <= rhs.maxX && lhs.maxX >= rhs.minX && lhs.minY <= rhs.maxY && lhs.maxY >= rhs.minY;
}

void PhysicsSystem::resolveCollisions(std::vector<PhysicsBody>& bodies, float dt) {
    for (auto& body : bodies) {
        body.bounds.minX += body.velocityX * dt;
        body.bounds.maxX += body.velocityX * dt;
        body.bounds.minY += body.velocityY * dt;
        body.bounds.maxY += body.velocityY * dt;
    }

    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            if (!intersects(bodies[i].bounds, bodies[j].bounds)) {
                continue;
            }
            std::swap(bodies[i].velocityX, bodies[j].velocityX);
            std::swap(bodies[i].velocityY, bodies[j].velocityY);
        }
    }
}

} // namespace goliaf
