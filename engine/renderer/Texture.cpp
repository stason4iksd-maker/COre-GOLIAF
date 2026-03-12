#include "renderer/Texture.h"

#include "core/Logger.h"

namespace core_goliaf::renderer {

bool Texture::load(const std::string& path) {
    core::Logger::info("Renderer", "Texture loaded: " + path + " (stub)");
    return true;
}

} // namespace core_goliaf::renderer
