#include <iostream>

#include "audio/AudioStub.hpp"
#include "physics/PhysicsStub.hpp"
#include "renderer/RendererStub.hpp"

int main() {
    std::cout << "Dev build started" << std::endl;
    std::cout << "[Dev] Tools: Level editor, menu editor, asset pipeline, debugging tools (stubs)." << std::endl;
    std::cout << "[Dev] Modules: " << renderer_name() << " | " << physics_name() << " | " << audio_name() << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}
