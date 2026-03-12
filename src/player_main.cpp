#include <iostream>

#include "audio/AudioStub.hpp"
#include "physics/PhysicsStub.hpp"
#include "renderer/RendererStub.hpp"

int main() {
    std::cout << "Player build started" << std::endl;
    std::cout << "[Player] Runtime initialized (stub)." << std::endl;
    std::cout << "[Player] Modules: " << renderer_name() << " | " << physics_name() << " | " << audio_name() << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}
