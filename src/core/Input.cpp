#include "core/Input.h"

namespace goliaf::core {

Input::Input(GLFWwindow* window) : window_(window) {}

void Input::Attach(GLFWwindow* window) {
    window_ = window;
    firstMouse_ = true;
}

void Input::Update(float) {
    if (!window_) return;

    moveForward_ = 0.0f;
    moveRight_ = 0.0f;
    yawDelta_ = 0.0f;
    pitchDelta_ = 0.0f;

    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) moveForward_ += 1.0f;
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) moveForward_ -= 1.0f;
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) moveRight_ += 1.0f;
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) moveRight_ -= 1.0f;

    double x = 0.0;
    double y = 0.0;
    glfwGetCursorPos(window_, &x, &y);

    if (firstMouse_) {
        lastX_ = x;
        lastY_ = y;
        firstMouse_ = false;
    }

    yawDelta_ = static_cast<float>(x - lastX_);
    pitchDelta_ = static_cast<float>(lastY_ - y);
    lastX_ = x;
    lastY_ = y;
}

}
