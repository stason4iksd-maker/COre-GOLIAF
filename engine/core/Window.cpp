#include "core/Window.h"

#include "core/Logger.h"

namespace core_goliaf::core {

bool Window::create(const std::string& title, int width, int height) {
    open_ = true;
    Logger::info("Window", "Created window '" + title + "' " + std::to_string(width) + "x" + std::to_string(height) + " (stub, GLFW/Win32-ready)");
    return true;
}

void Window::pollEvents() {
    if (open_) {
        Logger::info("Window", "Polling events (stub)");
    }
}

void Window::close() {
    open_ = false;
    Logger::info("Window", "Closed window");
}

bool Window::isOpen() const {
    return open_;
}

} // namespace core_goliaf::core
