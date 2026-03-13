#include "PhysicsSystem.h"

#include <gtest/gtest.h>

TEST(PhysicsSystemTest, DetectsAABBIntersection) {
    const goliaf::AABB a{0.0F, 0.0F, 2.0F, 2.0F};
    const goliaf::AABB b{1.0F, 1.0F, 3.0F, 3.0F};

    EXPECT_TRUE(goliaf::PhysicsSystem::intersects(a, b));
}

TEST(PhysicsSystemTest, DetectsAABBNonIntersection) {
    const goliaf::AABB a{0.0F, 0.0F, 1.0F, 1.0F};
    const goliaf::AABB b{2.0F, 2.0F, 3.0F, 3.0F};

    EXPECT_FALSE(goliaf::PhysicsSystem::intersects(a, b));
}
