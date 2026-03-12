#include <iostream>

#include "audio/AudioStub.h"
#include "physics/PhysicsStub.h"
#include "renderer/RendererStub.h"

int main() {
    std::cout << "Player build started" << std::endl;
    std::cout << "[Player] Runtime initialized (stub)." << std::endl;

    RendererStub renderer;
    PhysicsStub physics;
    AudioStub audio;

    renderer.initialize();
    renderer.renderFrame("PlayerViewport");
    physics.initialize();
    physics.update(1.0 / 60.0);
    audio.initialize();
    audio.update();

    std::cout << "[Player] Modules loaded successfully." << std::endl;
    return 0;
}
