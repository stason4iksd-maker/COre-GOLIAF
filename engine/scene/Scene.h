#pragma once

#include <string>
#include <vector>

namespace core_goliaf::scene {

struct SceneEntity {
    std::string name;
    std::vector<std::string> components;
};

class Scene {
public:
    explicit Scene(std::string sceneName = "Untitled") : name_(std::move(sceneName)) {}

    void addEntity(const SceneEntity& entity) { entities_.push_back(entity); }
    const std::string& name() const { return name_; }
    const std::vector<SceneEntity>& entities() const { return entities_; }

private:
    std::string name_;
    std::vector<SceneEntity> entities_;
};

} // namespace core_goliaf::scene
