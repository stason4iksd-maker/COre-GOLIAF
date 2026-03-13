#pragma once
#include <string>

namespace goliaf::renderer {

class Shader {
public:
    bool LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    void Use() const;
    unsigned int Id() const;
    ~Shader();
private:
    unsigned int program_ = 0;
};

}
