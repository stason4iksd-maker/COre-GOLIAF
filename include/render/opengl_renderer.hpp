#pragma once
#include <string>
#include <array>
struct GLFWwindow;

namespace render {

class OpenGLRenderer {
public:
    bool init(const std::string& title, int w = 1280, int h = 720);
    void beginFrame();
    void renderCube();
    void endFrame();
    bool shouldClose() const;
    GLFWwindow* window() const;
    void shutdown();
private:
    bool initCubeResources();
    unsigned int compileShader(unsigned int type, const char* src);

    GLFWwindow* window_{nullptr};
    unsigned int vao_{0};
    unsigned int vbo_{0};
    unsigned int program_{0};
};

}
