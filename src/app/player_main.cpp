#include "audio/audio_engine.hpp"
#include "ecs/ecs_world.hpp"
#include "ecs/scene_loader.hpp"
#include "physics/physics_world.hpp"
#include "render/opengl_renderer.hpp"
#include "scripting/lua_runtime.hpp"
#include <iostream>

int main() {
    std::cout << "Player build started\n";

    render::OpenGLRenderer renderer;
    if (!renderer.init("Player")) return 1;

    ecs::World world;
    ecs::SceneLoader loader;
    loader.load("assets/scenes/default.scene", world);
    auto cube = world.create();

    physics::PhysicsWorld physics;
    audio::AudioEngine audio;
    audio.init();

    scripting::LuaRuntime lua;
    lua.loadScript("assets/scripts/player.lua");

    while (!renderer.shouldClose()) {
        constexpr float dt = 1.0f / 60.0f;
        lua.hotReload();
        lua.callUpdate(dt);
        physics.step(world, dt);
        audio.update(dt);

        auto& tr = world.transform(cube);
        tr.x += 0.001f;

        renderer.beginFrame();
        renderer.renderCube();
        renderer.endFrame();
    }

    audio.shutdown();
    renderer.shutdown();
    return 0;
}
