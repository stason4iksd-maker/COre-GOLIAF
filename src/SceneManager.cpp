#include "SceneManager.h"

namespace goliaf {

Scene& SceneManager::createScene(const std::string& name) {
    auto created = std::make_unique<Scene>();
    auto* raw = created.get();
    scenes_[name] = std::move(created);
    if (!active_) {
        active_ = raw;
    }
    return *raw;
}

bool SceneManager::setActiveScene(const std::string& name) {
    const auto it = scenes_.find(name);
    if (it == scenes_.end()) {
        return false;
    }
    active_ = it->second.get();
    return true;
}

Scene* SceneManager::activeScene() {
    return active_;
}

} // namespace goliaf
