#include "scripting/lua_runtime.hpp"
#include <iostream>

namespace scripting {

LuaRuntime::LuaRuntime() {
    L_ = luaL_newstate();
    luaL_openlibs(L_);
}

LuaRuntime::~LuaRuntime() {
    if (L_) lua_close(L_);
}

bool LuaRuntime::loadScript(const std::filesystem::path& path) {
    scriptPath_ = path;
    ts_ = std::filesystem::last_write_time(scriptPath_);
    if (luaL_dofile(L_, scriptPath_.string().c_str()) != LUA_OK) {
        std::cerr << lua_tostring(L_, -1) << '\n';
        return false;
    }
    return true;
}

bool LuaRuntime::hotReload() {
    if (scriptPath_.empty()) return false;
    auto now = std::filesystem::last_write_time(scriptPath_);
    if (now == ts_) return true;
    ts_ = now;
    lua_close(L_);
    L_ = luaL_newstate();
    luaL_openlibs(L_);
    return loadScript(scriptPath_);
}

bool LuaRuntime::callUpdate(float dt) {
    lua_getglobal(L_, "update");
    if (!lua_isfunction(L_, -1)) {
        lua_pop(L_, 1);
        return false;
    }
    lua_pushnumber(L_, dt);
    if (lua_pcall(L_, 1, 0, 0) != LUA_OK) {
        std::cerr << lua_tostring(L_, -1) << '\n';
        return false;
    }
    return true;
}

}
