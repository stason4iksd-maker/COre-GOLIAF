#pragma once
#include "ecs/ecs_world.hpp"

namespace physics {

class PhysicsWorld {
public:
    void setGravity(float gravity);
    void step(ecs::World& world, float dt);
private:
    float gravity_{-9.81f};
};

}
