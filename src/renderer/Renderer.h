#pragma once
#include "renderer/Mesh.h"
#include "renderer/Shader.h"

struct GLFWwindow;

namespace goliaf::renderer {

class Renderer {
public:
    bool Initialize(GLFWwindow* window, const char* shaderBasePath);
    void BeginFrame(float r, float g, float b, float a) const;
    void RenderTriangle();
private:
    Shader shader_;
    Mesh mesh_;
};

}
