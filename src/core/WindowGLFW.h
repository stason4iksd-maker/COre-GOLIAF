#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace goliaf::core {

class WindowGLFW {
public:
    WindowGLFW();
    ~WindowGLFW();
    bool Create(const std::string& title, int width, int height);
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;
    GLFWwindow* Handle() const;
private:
    GLFWwindow* window_;
};

}
