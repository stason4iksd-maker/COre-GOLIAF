#pragma once
#include "ecs/Registry.h"

namespace goliaf::ecs {

class RenderSystem {
public:
    void Update(Registry& registry);
};

class ScriptSystem {
public:
    void Update(Registry& registry, float dt);
};

class PhysicsStubSystem {
public:
    void Update(Registry& registry, float dt);
};

}
