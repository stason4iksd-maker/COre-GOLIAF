#include "scene/SceneSerializer.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "core/Logger.h"

namespace goliaf::scene {
using nlohmann::json;

bool SceneSerializer::Save(Scene& scene, const std::string& path) {
    json j;
    j["name"] = scene.Name();
    j["entities"] = json::array();
    for (const auto& e : scene.GetRegistry().Entities()) {
        json item;
        item["id"] = e.id;
        item["name"] = e.name;
        if (auto* t = scene.GetRegistry().GetTransform(e.id)) {
            item["transform"] = {t->x, t->y, t->z};
        }
        if (auto* s = scene.GetRegistry().GetScript(e.id)) {
            item["script"] = s->path;
        }
        j["entities"].push_back(item);
    }
    std::ofstream out(path);
    if (!out.is_open()) return false;
    out << j.dump(2);
    core::Logger::Log("Scene", "Saved scene: " + path);
    return true;
}

bool SceneSerializer::Load(Scene& scene, const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        core::Logger::Log("Scene", "Failed to load scene: " + path);
        return false;
    }
    json j;
    in >> j;
    for (auto& item : j["entities"]) {
        auto e = scene.GetRegistry().CreateEntity(item.value("name", "Entity"));
        if (item.contains("transform")) {
            auto& t = scene.GetRegistry().AddTransform(e);
            t.x = item["transform"][0].get<float>();
            t.y = item["transform"][1].get<float>();
            t.z = item["transform"][2].get<float>();
        }
        scene.GetRegistry().AddMeshRenderer(e);
        if (item.contains("script")) {
            auto& s = scene.GetRegistry().AddScript(e);
            s.path = item["script"].get<std::string>();
        }
    }
    core::Logger::Log("Scene", "Loaded scene: " + path);
    return true;
}

}
