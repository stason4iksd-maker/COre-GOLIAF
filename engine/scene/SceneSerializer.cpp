#include "scene/SceneSerializer.h"

#include <fstream>

#include "core/Logger.h"

namespace core_goliaf::scene {

bool SceneSerializer::save(const Scene& scene, const std::string& path) const {
    std::ofstream out(path);
    if (!out.is_open()) {
        core::Logger::info("Scene", "Failed to save scene: " + path);
        return false;
    }

    out << "Scene: " << scene.name() << '\n';
    for (const auto& entity : scene.entities()) {
        out << "Entity: " << entity.name << '\n';
        for (const auto& component : entity.components) {
            out << "Component: " << component << '\n';
        }
    }

    core::Logger::info("Scene", "Scene saved to " + path);
    return true;
}

} // namespace core_goliaf::scene
