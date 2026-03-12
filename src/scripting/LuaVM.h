#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>

struct lua_State;

namespace goliaf::ecs { class Registry; }

namespace goliaf::scripting {

class LuaVM {
public:
    LuaVM();
    ~LuaVM();
    bool Initialize();
    bool LoadScript(const std::string& path);
    void UpdateEntity(goliaf::ecs::Registry& registry, unsigned int entity, float dt, const std::string& scriptPath);
private:
    lua_State* L_ = nullptr;
    std::unordered_map<std::string, std::filesystem::file_time_type> times_;
    void RegisterApi();
};

}
