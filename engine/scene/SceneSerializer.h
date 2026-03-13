#pragma once

#include <string>

#include "scene/Scene.h"

namespace core_goliaf::scene {

class SceneSerializer {
public:
    bool save(const Scene& scene, const std::string& path) const;
};

} // namespace core_goliaf::scene
