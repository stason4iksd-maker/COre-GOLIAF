#pragma once
#include <glm/glm.hpp>

namespace goliaf::renderer {

class Camera {
public:
    void SetPerspective(float fovDeg, float aspect, float nearPlane, float farPlane);
    void UpdateFromInput(float moveForward, float moveRight, float yawDelta, float pitchDelta, float dt);
    glm::mat4 View() const;
    glm::mat4 Projection() const { return projection_; }
    glm::vec3 Position() const { return position_; }

private:
    glm::vec3 position_{0.0f, 0.0f, 3.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    float yaw_{-90.0f};
    float pitch_{0.0f};
    glm::mat4 projection_{1.0f};
};

}
