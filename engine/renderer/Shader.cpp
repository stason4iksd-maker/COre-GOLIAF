#include "renderer/Shader.h"

#include "core/Logger.h"

namespace core_goliaf::renderer {

bool Shader::load(const std::string& name) {
    core::Logger::info("Renderer", "Shader loaded: " + name + " (stub)");
    return true;
}

} // namespace core_goliaf::renderer
