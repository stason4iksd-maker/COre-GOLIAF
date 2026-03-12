#include "renderer/Renderer.h"

#include "core/Logger.h"

namespace core_goliaf::renderer {

bool Renderer::initialize() {
    core::Logger::info("Renderer", "Initialized");
    core::Logger::info("Engine", "Renderer initialized");
    core::Logger::info("Renderer", "Backend abstraction ready (OpenGL/DirectX/Vulkan)");
    core::Logger::info("Renderer", "First test render prepared: colored background / triangle (stub)");
    return true;
}

void Renderer::render(double deltaTime) const {
    core::Logger::info("Renderer", "Render frame dt=" + std::to_string(deltaTime));
}

} // namespace core_goliaf::renderer
