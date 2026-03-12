#include "renderer/Shader.h"
#include "renderer/GLUtils.h"
#include "core/Logger.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>

namespace goliaf::renderer {

static std::string ReadText(const std::string& path) {
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

bool Shader::LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
    const auto vsSrc = ReadText(vertexPath);
    const auto fsSrc = ReadText(fragmentPath);
    if (vsSrc.empty() || fsSrc.empty()) {
        core::Logger::Log("Renderer", "Shader source missing");
        return false;
    }
    const char* vptr = vsSrc.c_str();
    const char* fptr = fsSrc.c_str();

    const unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vptr, nullptr);
    glCompileShader(vs);
    if (!CheckShader(vs, "Vertex")) return false;

    const unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fptr, nullptr);
    glCompileShader(fs);
    if (!CheckShader(fs, "Fragment")) return false;

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);
    const bool ok = CheckProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);

    if (ok) core::Logger::Log("Renderer", "Shader compiled");
    return ok;
}

void Shader::Use() const { glUseProgram(program_); }
unsigned int Shader::Id() const { return program_; }
Shader::~Shader() { if (program_ != 0) glDeleteProgram(program_); }

}
