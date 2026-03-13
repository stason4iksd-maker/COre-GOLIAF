#include "core/Application.h"
#include "core/Logger.h"

namespace goliaf::core {

bool Application::Initialize(const std::string& title, int width, int height) {
    if (!window_.Create(title, width, height)) {
        return false;
    }
    running_ = true;
    timer_.Reset();
    Logger::Log("Core", "initialized");
    return true;
}

void Application::Run(const UpdateCallback& update, const RenderCallback& render) {
    while (running_ && !window_.ShouldClose()) {
        const float dt = timer_.Tick();
        window_.PollEvents();
        if (update) update(dt);
        if (render) render();
        window_.SwapBuffers();
    }
}

void Application::Shutdown() {
    running_ = false;
    Logger::Log("Core", "shutdown");
}

WindowGLFW& Application::GetWindow() { return window_; }

}
