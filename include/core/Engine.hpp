#pragma once

#include <cstdint>

namespace goliaf {
class Scene;
class SceneManager;
class Renderer;
class PhysicsSystem;
class AudioManager;
}

class Engine {
public:
    bool initialize();
    void update(double deltaTime);
    void render();
    void shutdown();

    bool isRunning() const noexcept;
    void requestStop() noexcept;

private:
    bool initialized_{false};
    bool running_{false};
    std::uint64_t frameCounter_{0};
};
