#pragma once
#include <functional>
#include <string>

#include "core/Timer.h"
#include "core/WindowGLFW.h"

namespace goliaf::core {

class Application {
public:
    using UpdateCallback = std::function<void(float)>;
    using RenderCallback = std::function<void()>;

    bool Initialize(const std::string& title, int width, int height);
    void Run(const UpdateCallback& update, const RenderCallback& render);
    void Shutdown();
    WindowGLFW& GetWindow();
private:
    bool running_ = false;
    WindowGLFW window_;
    Timer timer_;
};

}
