#pragma once

#include <string>

namespace core_goliaf::renderer {

class Shader {
public:
    bool load(const std::string& name);
};

} // namespace core_goliaf::renderer
