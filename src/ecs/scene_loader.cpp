#include "ecs/scene_loader.hpp"
#include <fstream>
#include <string>

namespace ecs {
bool SceneLoader::load(const std::filesystem::path& scenePath, World& world) {
    std::ifstream in(scenePath);
    if (!in) return false;
    std::string line;
    while (std::getline(in, line)) {
        if (line.rfind("entity", 0) == 0) {
            world.create();
        }
    }
    return true;
}
}
