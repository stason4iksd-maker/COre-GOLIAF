#include "scene/SceneLoader.h"

#include "core/Logger.h"

namespace core_goliaf::scene {

Scene SceneLoader::load(const std::string& path) const {
    core::Logger::info("Scene", "Loading scene file: " + path + " (stub)");
    Scene scene{"level1.scene"};
    scene.addEntity({"Player", {"Transform", "Mesh", "Collider"}});
    return scene;
}

} // namespace core_goliaf::scene
