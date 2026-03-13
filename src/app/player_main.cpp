#include "ecs/ecs_world.hpp"
#include "ecs/scene_loader.hpp"
#include "render/opengl_renderer.hpp"
#include "scripting/lua_runtime.hpp"
#include <iostream>

int main() {
    render::OpenGLRenderer renderer;
    if (!renderer.init("Player")) return 1;

    ecs::World world;
    ecs::SceneLoader loader;
    loader.load("assets/scenes/default.scene", world);
    auto cube = world.create();

    scripting::LuaRuntime lua;
    lua.loadScript("assets/scripts/player.lua");

    while (!renderer.shouldClose()) {
        lua.hotReload();
        lua.callUpdate(0.016f);
        auto& tr = world.transform(cube);
        tr.x += 0.001f;

        renderer.beginFrame();
        renderer.renderCube();
        renderer.endFrame();
    }

    renderer.shutdown();
    return 0;
}
