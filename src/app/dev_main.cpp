#include "assets/pipeline.hpp"
#include "audio/audio_engine.hpp"
#include "ecs/ecs_world.hpp"
#include "editor/level_editor.hpp"
#include "editor/menu_editor.hpp"
#include "physics/physics_world.hpp"
#include "render/opengl_renderer.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

int main() {
    std::cout << "Dev build started\n";
    render::OpenGLRenderer renderer;
    if (!renderer.init("Dev Editor")) return 1;

    audio::AudioEngine audio;
    audio.init();

    ecs::World world;
    auto devCube = world.create();
    physics::PhysicsWorld physics;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    editor::MenuEditor menu;
    editor::LevelEditor level;
    assets::Pipeline pipeline;
    pipeline.importAssets("assets");
    pipeline.compileAndCache("build/cache");

    while (!renderer.shouldClose()) {
        constexpr float dt = 1.0f / 60.0f;
        physics.step(world, dt);
        audio.update(dt);

        renderer.beginFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menu.draw();
        level.draw();

        ImGui::Begin("Viewport");
        auto& tr = world.transform(devCube);
        ImGui::Text("3D viewport with cube + gizmos");
        ImGui::Text("Cube position: (%.2f, %.2f, %.2f)", tr.x, tr.y, tr.z);
        ImGui::Text("Debug: physics+audio running");
        ImGui::End();

        ImGui::Render();
        renderer.renderCube();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        renderer.endFrame();

        pipeline.shaderHotReload("shaders/default.glsl");
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    audio.shutdown();
    renderer.shutdown();
    return 0;
}
