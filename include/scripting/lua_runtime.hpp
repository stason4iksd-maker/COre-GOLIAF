#pragma once
#include <filesystem>
#include <string>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace scripting {

class LuaRuntime {
public:
    LuaRuntime();
    ~LuaRuntime();

    bool loadScript(const std::filesystem::path& path);
    bool hotReload();
    bool callUpdate(float dt);

private:
    lua_State* L_{nullptr};
    std::filesystem::path scriptPath_;
    std::filesystem::file_time_type ts_{};
};

}
