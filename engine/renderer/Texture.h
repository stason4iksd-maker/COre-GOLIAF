#pragma once

#include <string>

namespace core_goliaf::renderer {

class Texture {
public:
    bool load(const std::string& path);
};

} // namespace core_goliaf::renderer
