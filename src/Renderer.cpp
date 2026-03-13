#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace goliaf {

bool Renderer::init() {
    initialized_ = true;
    return initialized_;
}

void Renderer::shutdown() {
    initialized_ = false;
    shaderPrograms_.clear();
}

void Renderer::beginFrame() {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
    drawCalls_ = 0;
}

void Renderer::endFrame() {
    if (!initialized_) {
        throw std::runtime_error("renderer is not initialized");
    }
}

bool Renderer::loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& programName) {
    if (programName.empty()) {
        return false;
    }

    std::ifstream vertex(vertexPath);
    std::ifstream fragment(fragmentPath);
    if (!vertex.good() || !fragment.good()) {
        return false;
    }

    std::stringstream vertexBuffer;
    std::stringstream fragmentBuffer;
    vertexBuffer << vertex.rdbuf();
    fragmentBuffer << fragment.rdbuf();
    if (vertexBuffer.str().empty() || fragmentBuffer.str().empty()) {
        return false;
    }

    shaderPrograms_.insert(programName);
    return true;
}

void Renderer::drawMesh(const Mesh& mesh, const Material& material) {
    if (!isInitialized()) {
        throw std::runtime_error("renderer is not initialized");
    }
    if (mesh.vertices.empty() || mesh.indices.empty()) {
        return;
    }
    if (!material.shaderName.empty() && shaderPrograms_.count(material.shaderName) == 0) {
        throw std::runtime_error("unknown shader program");
    }
    ++drawCalls_;
}

bool Renderer::isInitialized() const noexcept { return initialized_; }
int Renderer::drawCalls() const noexcept { return drawCalls_; }
bool Renderer::hasShaderProgram(const std::string& programName) const {
    return shaderPrograms_.count(programName) > 0;
}

} // namespace goliaf
