#pragma once
#include <GLFW/glfw3.h>

namespace goliaf::core {

class Input {
public:
    explicit Input(GLFWwindow* window = nullptr);
    void Attach(GLFWwindow* window);
    void Update(float dt);

    float MoveForward() const { return moveForward_; }
    float MoveRight() const { return moveRight_; }
    float YawDelta() const { return yawDelta_; }
    float PitchDelta() const { return pitchDelta_; }

private:
    GLFWwindow* window_{};
    double lastX_{0.0};
    double lastY_{0.0};
    bool firstMouse_{true};
    float moveForward_{0.0f};
    float moveRight_{0.0f};
    float yawDelta_{0.0f};
    float pitchDelta_{0.0f};
};

}
