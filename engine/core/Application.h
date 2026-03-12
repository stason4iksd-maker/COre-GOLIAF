#pragma once

#include "audio/AudioEngine.h"
#include "core/Timer.h"
#include "core/Window.h"
#include "physics/PhysicsEngine.h"
#include "renderer/Renderer.h"

namespace core_goliaf::core {

class Application {
public:
    bool initialize(const char* title, int width, int height);
    void run(int maxFrames = 3);
    void shutdown();

private:
    bool running_ = false;
    Window window_;
    Timer timer_;
    renderer::Renderer renderer_;
    physics::PhysicsEngine physics_;
    audio::AudioEngine audio_;
};

} // namespace core_goliaf::core
