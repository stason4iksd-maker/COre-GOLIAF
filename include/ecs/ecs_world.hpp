#pragma once
#include <cstdint>
#include <unordered_map>

namespace ecs {

using Entity = std::uint32_t;

struct Transform { float x{}, y{}, z{}; };

class World {
public:
    Entity create();
    Transform& transform(Entity e);
    std::unordered_map<Entity, Transform>& transforms();
    const std::unordered_map<Entity, Transform>& transforms() const;
private:
    Entity next_{1};
    std::unordered_map<Entity, Transform> transforms_;
};

}
