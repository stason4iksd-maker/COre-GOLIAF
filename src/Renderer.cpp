#include "Renderer.h"

#include <fstream>
#include <stdexcept>

namespace goliaf {

bool Renderer::init() {
    initialized_ = true;
    return initialized_;
}

void Renderer::shutdown() {
    initialized_ = false;
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

bool Renderer::loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, std::string) {
    std::ifstream vertex(vertexPath);
    std::ifstream fragment(fragmentPath);
    return vertex.good() && fragment.good();
}

void Renderer::drawMesh(const Mesh& mesh, const Material&) {
    if (!isInitialized()) {
        throw std::runtime_error("renderer is not initialized");
    }
    if (mesh.vertices.empty() || mesh.indices.empty()) {
        return;
    }
    ++drawCalls_;
}

bool Renderer::isInitialized() const noexcept { return initialized_; }
int Renderer::drawCalls() const noexcept { return drawCalls_; }

} // namespace goliaf
