#include "core/AudioSystem.hpp"
#include "core/EcsWorld.hpp"
#include "core/Engine.hpp"
#include "core/PhysicsSystem.hpp"
#include "core/Renderer.hpp"

int main() {
    Engine engine;
    Renderer renderer;
    PhysicsSystem physics;
    AudioSystem audio;
    EcsWorld ecs;

    engine.initialize();
    renderer.initialize();
    physics.initialize();
    audio.initialize();
    ecs.initialize();

    engine.update(1.0 / 60.0);
    physics.step(1.0 / 60.0);
    ecs.tick(1.0 / 60.0);
    audio.update();
    renderer.renderFrame("PlayerViewport");

    engine.shutdown();
    return 0;
}
