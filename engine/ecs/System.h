#pragma once

#include "core/Logger.h"

namespace core_goliaf::ecs {

class RenderSystem {
public:
    void update() const { core::Logger::info("ECS", "RenderSystem update"); }
};

class PhysicsSystem {
public:
    void update() const { core::Logger::info("ECS", "PhysicsSystem update"); }
};

class InputSystem {
public:
    void update() const { core::Logger::info("ECS", "InputSystem update"); }
};

} // namespace core_goliaf::ecs
