#include "core/Application.h"
#include "core/Input.h"
#include "core/Logger.h"
#include "network/NetworkClient.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"
#include "scene/SceneSerializer.h"
#include "scripting/LuaVM.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nlohmann/json.hpp>

int main() {
    goliaf::core::Logger::Log("Player", "Runtime initialized");

    goliaf::core::Application app;
    if (!app.Initialize("COre-GOLIAF Player", 1280, 720)) return 1;

    goliaf::renderer::Renderer renderer;
    if (!renderer.Initialize(app.GetWindow().Handle(), "assets/shaders")) return 2;

    goliaf::renderer::Camera camera;
    camera.SetPerspective(60.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    goliaf::core::Input input(app.GetWindow().Handle());

    goliaf::scene::Scene scene("PlayerScene");
    goliaf::scene::SceneSerializer serializer;
    serializer.Load(scene, "assets/scenes/level1.scene.json");

    goliaf::scripting::LuaVM lua;
    lua.Initialize();

    goliaf::network::NetworkClient client;
    if (client.Connect("127.0.0.1", 12345)) {
        client.SendJson(R"({"type":"connect","payload":{"player":"local"}})");
    }

    app.Run([&](float dt) {
        input.Update(dt);
        camera.UpdateFromInput(input.MoveForward(), input.MoveRight(), input.YawDelta(), input.PitchDelta(), dt);

        for (const auto& e : scene.GetRegistry().Entities()) {
            if (auto* sc = scene.GetRegistry().GetScript(e.id)) {
                lua.UpdateEntity(scene.GetRegistry(), e.id, dt, sc->path);
            }
        }

        nlohmann::json pos;
        pos["type"] = "position";
        pos["payload"] = { {"x", camera.Position().x}, {"y", camera.Position().y}, {"z", camera.Position().z} };
        client.SendJson(pos.dump());
        const auto reply = client.Receive();
        if (!reply.empty()) goliaf::core::Logger::Log("Player", "Net: " + reply);

    }, [&]() {
        renderer.BeginFrame(0.08f, 0.07f, 0.10f, 1.0f);

        for (const auto& e : scene.GetRegistry().Entities()) {
            auto* t = scene.GetRegistry().GetTransform(e.id);
            if (!t) continue;
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(t->x, t->y, t->z));
            renderer.RenderCube(model, camera.View(), camera.Projection());
        }
    });

    client.Close();
    app.Shutdown();
    return 0;
}
