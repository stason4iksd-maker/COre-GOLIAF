#pragma once

#include <string>

namespace core_goliaf::ecs {

struct IComponent {
    virtual ~IComponent() = default;
};

struct Transform : IComponent {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};
};

struct MeshRenderer : IComponent {
    std::string meshName{"default.mesh"};
};

struct RigidBody : IComponent {
    float mass{1.0F};
};

} // namespace core_goliaf::ecs
