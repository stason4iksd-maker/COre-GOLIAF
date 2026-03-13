#include "ecs/ecs_world.hpp"

namespace ecs {
Entity World::create() {
    Entity e = next_++;
    transforms_.emplace(e, Transform{});
    return e;
}
Transform& World::transform(Entity e) { return transforms_.at(e); }
const std::unordered_map<Entity, Transform>& World::transforms() const { return transforms_; }
}
