#include "scene/Scene.h"

namespace goliaf::scene {
Scene::Scene(std::string name) : name_(std::move(name)) {}
const std::string& Scene::Name() const { return name_; }
goliaf::ecs::Registry& Scene::GetRegistry() { return registry_; }
}
