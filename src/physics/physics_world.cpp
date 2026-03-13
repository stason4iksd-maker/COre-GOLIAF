#include "physics/physics_world.hpp"

namespace physics {

void PhysicsWorld::setGravity(float gravity) { gravity_ = gravity; }

void PhysicsWorld::step(ecs::World& world, float dt) {
    for (auto& [entity, transform] : world.transforms()) {
        (void)entity;
        transform.y += gravity_ * dt;
        if (transform.y < -1.0f) transform.y = -1.0f;
    }
}

}
