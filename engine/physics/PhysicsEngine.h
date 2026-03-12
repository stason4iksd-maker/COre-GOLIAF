#pragma once

namespace core_goliaf::physics {

class PhysicsEngine {
public:
    bool initialize();
    void update(double deltaTime) const;
};

} // namespace core_goliaf::physics
