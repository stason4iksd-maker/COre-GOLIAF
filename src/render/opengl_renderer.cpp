#include "render/opengl_renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {
constexpr const char* kVs = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform float offset;
void main(){ gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0); }
)";

constexpr const char* kFs = R"(
#version 330 core
out vec4 FragColor;
void main(){ FragColor = vec4(0.4, 0.8, 0.4, 1.0); }
)";
}

namespace render {

unsigned int OpenGLRenderer::compileShader(unsigned int type, const char* src) {
    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

bool OpenGLRenderer::initCubeResources() {
    const float vertices[] = {
      -0.5f,-0.5f,0.f,  0.5f,-0.5f,0.f,  0.5f,0.5f,0.f,
      -0.5f,-0.5f,0.f,  0.5f,0.5f,0.f,  -0.5f,0.5f,0.f
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto vs = compileShader(GL_VERTEX_SHADER, kVs);
    auto fs = compileShader(GL_FRAGMENT_SHADER, kFs);
    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return true;
}

bool OpenGLRenderer::init(const std::string& title, int w, int h) {
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!window_) return false;
    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;
    glEnable(GL_DEPTH_TEST);
    return initCubeResources();
}

void OpenGLRenderer::beginFrame() {
    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::renderCube() {
    glUseProgram(program_);
    glUniform1f(glGetUniformLocation(program_, "offset"), 0.0f);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLRenderer::endFrame() { glfwSwapBuffers(window_); }

bool OpenGLRenderer::shouldClose() const { return !window_ || glfwWindowShouldClose(window_); }
GLFWwindow* OpenGLRenderer::window() const { return window_; }

void OpenGLRenderer::shutdown() {
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (program_) glDeleteProgram(program_);
    if (window_) glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
}

}
