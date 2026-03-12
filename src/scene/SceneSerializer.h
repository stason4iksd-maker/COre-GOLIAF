#pragma once
#include <string>
#include "scene/Scene.h"

namespace goliaf::scene {

class SceneSerializer {
public:
    bool Save(Scene& scene, const std::string& path);
    bool Load(Scene& scene, const std::string& path);
};

}
