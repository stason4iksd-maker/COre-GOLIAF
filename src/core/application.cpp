#include "core/application.hpp"
#include <chrono>
#include <thread>

namespace core {

Application::Application(std::string name) : name_(std::move(name)) {}

void Application::run() {
    using clock = std::chrono::steady_clock;
    auto prev = clock::now();
    while (running_) {
        auto now = clock::now();
        float dt = std::chrono::duration<float>(now - prev).count();
        prev = now;
        if (module_) module_->update(dt);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Application::stop() { running_ = false; }

void Application::setModule(std::shared_ptr<IModule> module) { module_ = std::move(module); }

}
