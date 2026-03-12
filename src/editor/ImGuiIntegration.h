#pragma once
struct GLFWwindow;

namespace goliaf::editor {

class ImGuiIntegration {
public:
    bool Initialize(GLFWwindow* window);
    void BeginFrame();
    void EndFrame();
    void Shutdown();
};

}
