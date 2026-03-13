#pragma once
#include "ecs_world.hpp"
#include <filesystem>

namespace ecs {
class SceneLoader {
public:
    bool load(const std::filesystem::path& scenePath, World& world);
};
}
