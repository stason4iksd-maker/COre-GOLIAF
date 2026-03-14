#include "ResourceManager.h"

#include <gtest/gtest.h>

TEST(ResourceManagerTest, LoadsSameResourceOnlyOnce) {
    auto& manager = goliaf::ResourceManager::instance();
    manager.clear();

    auto first = manager.loadTexture("assets/textures/test.png");
    auto second = manager.loadTexture("assets/textures/test.png");

    EXPECT_EQ(first.get(), second.get());
    EXPECT_EQ(first->id(), "assets/textures/test.png");

    manager.clear();
}

TEST(ResourceManagerTest, NormalizesPathForCachingAndRelease) {
    auto& manager = goliaf::ResourceManager::instance();
    manager.clear();

    auto first = manager.loadTexture("assets/textures/../textures/test.png");
    auto second = manager.GetResource("assets/textures/test.png");

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(first.get(), second.get());

    manager.ReleaseResource("assets/textures/./test.png");
    EXPECT_EQ(manager.getResource("assets/textures/test.png"), nullptr);
}
