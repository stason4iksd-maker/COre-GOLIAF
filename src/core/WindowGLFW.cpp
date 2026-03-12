#include "core/WindowGLFW.h"
#include "core/Logger.h"

namespace goliaf::core {

WindowGLFW::WindowGLFW() : window_(nullptr) {}
WindowGLFW::~WindowGLFW() {
    if (window_) {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
}

bool WindowGLFW::Create(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        Logger::Log("Core", "glfwInit failed");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        Logger::Log("Core", "Failed to create window");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    Logger::Log("Core", "Window created");
    return true;
}

void WindowGLFW::PollEvents() { glfwPollEvents(); }
void WindowGLFW::SwapBuffers() { glfwSwapBuffers(window_); }
bool WindowGLFW::ShouldClose() const { return glfwWindowShouldClose(window_); }
GLFWwindow* WindowGLFW::Handle() const { return window_; }

}
