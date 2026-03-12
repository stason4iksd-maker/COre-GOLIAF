#include "scripting/LuaVM.h"

#include <lua.hpp>

#include "core/Logger.h"
#include "ecs/Registry.h"

namespace goliaf::scripting {

LuaVM::LuaVM() = default;
LuaVM::~LuaVM() {
    if (L_) lua_close(L_);
}

bool LuaVM::Initialize() {
    L_ = luaL_newstate();
    if (!L_) return false;
    luaL_openlibs(L_);
    RegisterApi();
    core::Logger::Log("Scripting", "Lua initialized");
    return true;
}

void LuaVM::RegisterApi() {
    lua_pushcfunction(L_, [](lua_State* L) -> int {
        const double x = luaL_checknumber(L, 1);
        const double y = luaL_checknumber(L, 2);
        const double z = luaL_checknumber(L, 3);
        lua_pushnumber(L, x + y + z);
        return 1;
    });
    lua_setglobal(L_, "sum3");
}

bool LuaVM::LoadScript(const std::string& path) {
    if (luaL_dofile(L_, path.c_str()) != LUA_OK) {
        core::Logger::Log("Scripting", std::string("Lua error: ") + lua_tostring(L_, -1));
        lua_pop(L_, 1);
        return false;
    }
    times_[path] = std::filesystem::last_write_time(path);
    core::Logger::Log("Scripting", "Script loaded: " + path);
    return true;
}

void LuaVM::UpdateEntity(goliaf::ecs::Registry& registry, unsigned int entity, float dt, const std::string& scriptPath) {
    if (!L_) return;
    if (std::filesystem::exists(scriptPath)) {
        const auto current = std::filesystem::last_write_time(scriptPath);
        auto it = times_.find(scriptPath);
        if (it == times_.end() || current != it->second) {
            core::Logger::Log("Scripting", "Hot-reload: " + scriptPath);
            LoadScript(scriptPath);
        }
    }

    auto* tr = registry.GetTransform(entity);
    if (!tr) return;

    lua_getglobal(L_, "on_update");
    if (!lua_isfunction(L_, -1)) {
        lua_pop(L_, 1);
        return;
    }
    lua_pushnumber(L_, tr->x);
    lua_pushnumber(L_, tr->y);
    lua_pushnumber(L_, tr->z);
    lua_pushnumber(L_, dt);
    if (lua_pcall(L_, 4, 3, 0) != LUA_OK) {
        core::Logger::Log("Scripting", std::string("on_update failed: ") + lua_tostring(L_, -1));
        lua_pop(L_, 1);
        return;
    }
    tr->x = static_cast<float>(lua_tonumber(L_, -3));
    tr->y = static_cast<float>(lua_tonumber(L_, -2));
    tr->z = static_cast<float>(lua_tonumber(L_, -1));
    lua_pop(L_, 3);
}

}
