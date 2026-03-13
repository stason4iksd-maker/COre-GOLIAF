#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace goliaf {

struct Mesh {
    std::vector<float> vertices;
    std::vector<std::uint32_t> indices;
};

struct Material {
    std::string shaderName;
    std::vector<std::string> texturePaths;
};

class Renderer {
public:
    bool init();
    void shutdown();

    void beginFrame();
    void endFrame();

    bool loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, std::string programName);
    void drawMesh(const Mesh& mesh, const Material& material);

    [[nodiscard]] bool isInitialized() const noexcept;
    [[nodiscard]] int drawCalls() const noexcept;

private:
    bool initialized_{false};
    int drawCalls_{0};
};

} // namespace goliaf
