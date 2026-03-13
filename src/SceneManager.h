#pragma once

#include "Scene.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace goliaf {

class SceneManager {
public:
    Scene& createScene(const std::string& name);
    bool setActiveScene(const std::string& name);
    Scene* activeScene();

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes_;
    Scene* active_{nullptr};
};

} // namespace goliaf
