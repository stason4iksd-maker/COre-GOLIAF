#pragma once
#include <glm/mat4x4.hpp>

#include "renderer/Mesh.h"
#include "renderer/Shader.h"

struct GLFWwindow;

namespace goliaf::renderer {

class Renderer {
public:
    bool Initialize(GLFWwindow* window, const char* shaderBasePath);
    void BeginFrame(float r, float g, float b, float a) const;
    void RenderCube(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
private:
    Shader shader_;
    Mesh mesh_;
};

}
