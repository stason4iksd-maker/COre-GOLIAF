#include "core/Application.h"
#include "core/Input.h"
#include "core/Logger.h"
#include "editor/EditorApp.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"
#include "scene/SceneSerializer.h"
#include "scripting/LuaVM.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
    goliaf::core::Application app;
    if (!app.Initialize("COre-GOLIAF Dev", 1280, 720)) return 1;

    goliaf::renderer::Renderer renderer;
    if (!renderer.Initialize(app.GetWindow().Handle(), "assets/shaders")) return 2;

    goliaf::renderer::Camera camera;
    camera.SetPerspective(60.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    goliaf::core::Input input(app.GetWindow().Handle());

    goliaf::scene::Scene scene("DevScene");
    goliaf::scene::SceneSerializer serializer;
    std::string scenePath = "assets/scenes/level1.scene.json";
    serializer.Load(scene, scenePath);

    goliaf::scripting::LuaVM lua;
    lua.Initialize();

    goliaf::editor::EditorApp editor;
    editor.Initialize(app.GetWindow().Handle());

    app.Run([&](float dt) {
        input.Update(dt);
        camera.UpdateFromInput(input.MoveForward(), input.MoveRight(), input.YawDelta(), input.PitchDelta(), dt);

        for (const auto& e : scene.GetRegistry().Entities()) {
            if (auto* sc = scene.GetRegistry().GetScript(e.id)) {
                lua.UpdateEntity(scene.GetRegistry(), e.id, dt, sc->path);
            }
        }
    }, [&]() {
        renderer.BeginFrame(0.10f, 0.12f, 0.17f, 1.0f);

        for (const auto& e : scene.GetRegistry().Entities()) {
            auto* t = scene.GetRegistry().GetTransform(e.id);
            if (!t) continue;
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(t->x, t->y, t->z));
            renderer.RenderCube(model, camera.View(), camera.Projection());
        }

        editor.RenderUI(scene.GetRegistry(), scenePath);
    });

    serializer.Save(scene, scenePath);
    editor.Shutdown();
    app.Shutdown();
    return 0;
}
