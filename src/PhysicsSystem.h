#pragma once

#include <vector>

namespace goliaf {

struct AABB {
    float minX;
    float minY;
    float maxX;
    float maxY;
};

struct PhysicsBody {
    AABB bounds;
    float mass{1.0F};
    float velocityX{0.0F};
    float velocityY{0.0F};
};

class PhysicsSystem {
public:
    static bool intersects(const AABB& lhs, const AABB& rhs);
    void resolveCollisions(std::vector<PhysicsBody>& bodies, float dt);
};

} // namespace goliaf
