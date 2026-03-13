#include "Scene.h"

#include <gtest/gtest.h>

TEST(SceneTest, TransformHierarchyComputesWorldPosition) {
    goliaf::Scene scene;
    auto& parent = scene.addEntity();
    auto& child = scene.addEntity();

    auto& parentTransform = parent.addComponent<goliaf::TransformComponent>(goliaf::Vec3{1.0F, 2.0F, 3.0F});
    auto& childTransform = child.addComponent<goliaf::TransformComponent>(goliaf::Vec3{4.0F, 5.0F, 6.0F});

    childTransform.setParent(&parentTransform);
    const auto worldPos = childTransform.worldPosition();

    EXPECT_FLOAT_EQ(worldPos.x, 5.0F);
    EXPECT_FLOAT_EQ(worldPos.y, 7.0F);
    EXPECT_FLOAT_EQ(worldPos.z, 9.0F);
}
