#include "Renderer.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

TEST(RendererTest, InitSucceeds) {
    goliaf::Renderer renderer;
    EXPECT_TRUE(renderer.init());
    EXPECT_TRUE(renderer.isInitialized());
    renderer.shutdown();
}

TEST(RendererTest, LoadsShaderProgramFromFiles) {
    const auto tempDir = std::filesystem::temp_directory_path();
    const auto vertPath = tempDir / "goliaf_test_shader.vert";
    const auto fragPath = tempDir / "goliaf_test_shader.frag";

    {
        std::ofstream vert(vertPath);
        std::ofstream frag(fragPath);
        vert << "#version 330 core\nvoid main(){gl_Position=vec4(0.0);}";
        frag << "#version 330 core\nout vec4 c; void main(){c=vec4(1.0);}";
    }

    goliaf::Renderer renderer;
    ASSERT_TRUE(renderer.init());
    EXPECT_TRUE(renderer.loadShaderProgram(vertPath.string(), fragPath.string(), "default"));
    EXPECT_TRUE(renderer.hasShaderProgram("default"));

    std::filesystem::remove(vertPath);
    std::filesystem::remove(fragPath);
}
