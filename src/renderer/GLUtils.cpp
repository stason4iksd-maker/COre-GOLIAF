#include "renderer/GLUtils.h"
#include "core/Logger.h"
#include <GL/glew.h>
#include <vector>

namespace goliaf::renderer {

bool CheckShader(unsigned int shader, const std::string& type) {
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return true;
    int len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> log(len);
    glGetShaderInfoLog(shader, len, nullptr, log.data());
    core::Logger::Log("Renderer", type + " compile error: " + std::string(log.data()));
    return false;
}

bool CheckProgram(unsigned int program) {
    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) return true;
    int len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> log(len);
    glGetProgramInfoLog(program, len, nullptr, log.data());
    core::Logger::Log("Renderer", "Program link error: " + std::string(log.data()));
    return false;
}

}
