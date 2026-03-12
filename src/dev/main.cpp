#include "core/AssetCompiler.hpp"
#include "core/AudioSystem.hpp"
#include "core/EcsWorld.hpp"
#include "core/Engine.hpp"
#include "core/LevelEditor.hpp"
#include "core/MenuEditor.hpp"
#include "core/PhysicsSystem.hpp"
#include "core/Renderer.hpp"

int main() {
    Engine engine;
    Renderer renderer;
    PhysicsSystem physics;
    AudioSystem audio;
    EcsWorld ecs;
    LevelEditor levelEditor;
    MenuEditor menuEditor;
    AssetCompiler assetCompiler;

    engine.initialize();
    renderer.initialize();
    physics.initialize();
    audio.initialize();
    ecs.initialize();

    levelEditor.open();
    menuEditor.open();
    assetCompiler.run();

    engine.update(1.0 / 60.0);
    physics.step(1.0 / 60.0);
    ecs.tick(1.0 / 60.0);
    audio.update();
    renderer.renderFrame("DevViewport");

    engine.shutdown();
    return 0;
}
