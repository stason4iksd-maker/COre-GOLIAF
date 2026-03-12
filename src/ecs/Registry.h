#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ecs/Component.h"
#include "ecs/Entity.h"

namespace goliaf::ecs {

class Registry {
public:
    Entity CreateEntity(const std::string& name);
    const std::vector<EntityInfo>& Entities() const;

    Transform& AddTransform(Entity e);
    MeshRenderer& AddMeshRenderer(Entity e);
    Camera& AddCamera(Entity e);
    Script& AddScript(Entity e);

    Transform* GetTransform(Entity e);
    MeshRenderer* GetMeshRenderer(Entity e);
    Camera* GetCamera(Entity e);
    Script* GetScript(Entity e);

    void ForEachTransform(const std::function<void(Entity, Transform&)>& fn);
private:
    Entity next_ = 1;
    std::vector<EntityInfo> entities_;
    std::unordered_map<Entity, Transform> transforms_;
    std::unordered_map<Entity, MeshRenderer> meshes_;
    std::unordered_map<Entity, Camera> cameras_;
    std::unordered_map<Entity, Script> scripts_;
};

}
