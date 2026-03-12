#include "renderer/Renderer.h"
#include "core/Logger.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace goliaf::renderer {

bool Renderer::Initialize(GLFWwindow* window, const char* shaderBasePath) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        core::Logger::Log("Renderer", "Failed to initialize GLEW");
        return false;
    }
    int w = 0;
    int h = 0;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    const std::string base(shaderBasePath);
    if (!shader_.LoadFromFiles(base + "/simple.vert", base + "/simple.frag")) {
        return false;
    }
    mesh_.CreateCube();
    core::Logger::Log("Renderer", "OpenGL initialized");
    return true;
}

void Renderer::BeginFrame(float r, float g, float b, float a) const {
    glEnable(GL_DEPTH_TEST);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderCube(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    shader_.Use();
    shader_.SetMat4("uModel", model);
    shader_.SetMat4("uView", view);
    shader_.SetMat4("uProj", projection);
    mesh_.Draw();
    core::Logger::Log("Renderer", "Rendering frame");
}

}
