#pragma once
#include <string>
#include <glm/mat4x4.hpp>

namespace goliaf::renderer {

class Shader {
public:
    bool LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    void Use() const;
    void SetMat4(const char* name, const glm::mat4& value) const;
    unsigned int Id() const;
    ~Shader();
private:
    unsigned int program_ = 0;
};

}
