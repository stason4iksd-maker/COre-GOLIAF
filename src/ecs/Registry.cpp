#include "ecs/Registry.h"

namespace goliaf::ecs {

Entity Registry::CreateEntity(const std::string& name) {
    const Entity id = next_++;
    entities_.push_back({id, name});
    return id;
}

const std::vector<EntityInfo>& Registry::Entities() const { return entities_; }

Transform& Registry::AddTransform(Entity e) { return transforms_[e]; }
MeshRenderer& Registry::AddMeshRenderer(Entity e) { return meshes_[e]; }
Camera& Registry::AddCamera(Entity e) { return cameras_[e]; }
Script& Registry::AddScript(Entity e) { return scripts_[e]; }

Transform* Registry::GetTransform(Entity e) {
    auto it = transforms_.find(e); return it == transforms_.end() ? nullptr : &it->second;
}
MeshRenderer* Registry::GetMeshRenderer(Entity e) {
    auto it = meshes_.find(e); return it == meshes_.end() ? nullptr : &it->second;
}
Camera* Registry::GetCamera(Entity e) {
    auto it = cameras_.find(e); return it == cameras_.end() ? nullptr : &it->second;
}
Script* Registry::GetScript(Entity e) {
    auto it = scripts_.find(e); return it == scripts_.end() ? nullptr : &it->second;
}

void Registry::ForEachTransform(const std::function<void(Entity, Transform&)>& fn) {
    for (auto& kv : transforms_) fn(kv.first, kv.second);
}

}
