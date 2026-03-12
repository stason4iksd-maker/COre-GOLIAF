#include "renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace goliaf::renderer {

void Camera::SetPerspective(float fovDeg, float aspect, float nearPlane, float farPlane) {
    projection_ = glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);
}

void Camera::UpdateFromInput(float moveForward, float moveRight, float yawDelta, float pitchDelta, float dt) {
    const float mouseSensitivity = 0.08f;
    const float speed = 3.5f;

    yaw_ += yawDelta * mouseSensitivity;
    pitch_ += pitchDelta * mouseSensitivity;
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    const glm::vec3 right = glm::normalize(glm::cross(front_, up_));
    position_ += front_ * moveForward * speed * dt;
    position_ += right * moveRight * speed * dt;
}

glm::mat4 Camera::View() const {
    return glm::lookAt(position_, position_ + front_, up_);
}

}
