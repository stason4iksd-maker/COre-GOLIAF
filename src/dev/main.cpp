#include "core/Application.h"
#include "core/Logger.h"
#include "dev/AssetPipeline.h"
#include "dev/debug/DebugTools.h"
#include "dev/editor/Editor.h"
#include "dev/level_editor/LevelEditor.h"
#include "dev/menu_editor/MenuEditor.h"
#include "ecs/EcsWorld.h"
#include "ecs/System.h"
#include "scene/SceneLoader.h"
#include "scene/SceneSerializer.h"

int main() {
    core_goliaf::core::Logger::info("Dev", "Dev build started");

    core_goliaf::core::Application app;
    app.initialize("COre-GOLIAF Dev", 1280, 720);

    core_goliaf::dev::Editor editor;
    core_goliaf::dev::LevelEditor levelEditor;
    core_goliaf::dev::MenuEditor menuEditor;
    core_goliaf::dev::AssetPipeline pipeline;
    core_goliaf::dev::DebugTools debugTools;

    editor.initialize();
    levelEditor.initialize();
    menuEditor.initialize();
    pipeline.initialize();

    core_goliaf::ecs::EcsWorld world;
    auto& player = world.createEntity();
    player.addComponent<core_goliaf::ecs::Transform>();
    player.addComponent<core_goliaf::ecs::MeshRenderer>();
    player.addComponent<core_goliaf::ecs::RigidBody>();

    core_goliaf::ecs::InputSystem inputSystem;
    core_goliaf::ecs::PhysicsSystem physicsSystem;
    core_goliaf::ecs::RenderSystem renderSystem;
    inputSystem.update();
    physicsSystem.update();
    renderSystem.update();

    core_goliaf::scene::SceneLoader loader;
    core_goliaf::scene::SceneSerializer serializer;
    auto scene = loader.load("assets/level1.scene");
    serializer.save(scene, "assets/level1.scene");

    app.run(2);
    debugTools.printFrameStats(60.0, 128.0);
    app.shutdown();

    return 0;
}
