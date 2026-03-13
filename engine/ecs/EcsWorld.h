#pragma once

#include <vector>

#include "ecs/Entity.h"

namespace core_goliaf::ecs {

class EcsWorld {
public:
    Entity& createEntity();

private:
    int nextId_ = 1;
    std::vector<Entity> entities_;
};

} // namespace core_goliaf::ecs
