#include <iostream>

#include "audio/AudioStub.h"
#include "physics/PhysicsStub.h"
#include "renderer/RendererStub.h"

int main() {
    std::cout << "Dev build started" << std::endl;
    std::cout << "[Dev] Level editor initialized (stub)." << std::endl;
    std::cout << "[Dev] Menu editor initialized (stub)." << std::endl;

    RendererStub renderer;
    PhysicsStub physics;
    AudioStub audio;

    renderer.initialize();
    physics.initialize();
    audio.initialize();

    renderer.renderFrame("DevViewport");
    physics.update(1.0 / 60.0);
    audio.update();

    std::cout << "[Dev] Asset pipeline ready (stub)." << std::endl;
    std::cout << "[Dev] Debug tools ready (stub)." << std::endl;
    return 0;
}
