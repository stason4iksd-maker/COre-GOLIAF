#pragma once

#include <string>

#include "scene/Scene.h"

namespace core_goliaf::scene {

class SceneLoader {
public:
    Scene load(const std::string& path) const;
};

} // namespace core_goliaf::scene
