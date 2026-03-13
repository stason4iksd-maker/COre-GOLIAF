#include "Renderer.h"

#include <gtest/gtest.h>

TEST(RendererTest, InitSucceeds) {
    goliaf::Renderer renderer;
    EXPECT_TRUE(renderer.init());
    EXPECT_TRUE(renderer.isInitialized());
    renderer.shutdown();
}
