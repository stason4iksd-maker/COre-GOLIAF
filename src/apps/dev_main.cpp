#include "core/Application.h"
#include "core/Logger.h"
#include "editor/EditorApp.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"
#include "scene/SceneSerializer.h"
#include "scripting/LuaVM.h"

int main() {
    goliaf::core::Application app;
    if (!app.Initialize("COre-GOLIAF Dev", 1280, 720)) return 1;

    goliaf::renderer::Renderer renderer;
    if (!renderer.Initialize(app.GetWindow().Handle(), "assets/shaders")) return 2;

    goliaf::scene::Scene scene("DevScene");
    goliaf::scene::SceneSerializer serializer;
    std::string scenePath = "assets/scenes/level1.scene.json";
    serializer.Load(scene, scenePath);

    goliaf::scripting::LuaVM lua;
    lua.Initialize();

    goliaf::editor::EditorApp editor;
    editor.Initialize(app.GetWindow().Handle());

    app.Run([&](float dt) {
        for (const auto& e : scene.GetRegistry().Entities()) {
            if (auto* sc = scene.GetRegistry().GetScript(e.id)) {
                lua.UpdateEntity(scene.GetRegistry(), e.id, dt, sc->path);
            }
        }
    }, [&]() {
        renderer.BeginFrame(0.10f, 0.12f, 0.17f, 1.0f);
        renderer.RenderTriangle();
        editor.RenderUI(scene.GetRegistry(), scenePath);
    });

    serializer.Save(scene, scenePath);
    editor.Shutdown();
    app.Shutdown();
    return 0;
}
