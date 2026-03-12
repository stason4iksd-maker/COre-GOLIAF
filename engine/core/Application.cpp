#include "core/Application.h"

#include "core/Logger.h"

namespace core_goliaf::core {

bool Application::initialize(const char* title, int width, int height) {
    Logger::info("Engine", "Application initializing");
    window_.create(title, width, height);
    renderer_.initialize();
    physics_.initialize();
    audio_.initialize();
    timer_.reset();
    running_ = true;
    return true;
}

void Application::run(int maxFrames) {
    int frame = 0;
    while (running_ && window_.isOpen() && frame < maxFrames) {
        const double deltaTime = timer_.tick();

        // Core loop target:
        // while(running) { Input.Update(); Physics.Update(); Renderer.Render(); }
        Logger::info("Input", "Update (stub)");
        physics_.update(deltaTime);
        renderer_.render(deltaTime);
        audio_.update();

        window_.pollEvents();
        ++frame;
    }
}

void Application::shutdown() {
    running_ = false;
    window_.close();
    Logger::info("Engine", "Application shutdown");
}

} // namespace core_goliaf::core
