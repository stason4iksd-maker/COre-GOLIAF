#include "ecs/EcsWorld.h"

namespace core_goliaf::ecs {

Entity& EcsWorld::createEntity() {
    entities_.emplace_back(nextId_++);
    return entities_.back();
}

} // namespace core_goliaf::ecs
