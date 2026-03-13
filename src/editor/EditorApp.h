#pragma once
#include <filesystem>
#include <string>

#include "ecs/Registry.h"
#include "editor/ImGuiIntegration.h"

namespace goliaf::editor {

class EditorApp {
public:
    bool Initialize(struct GLFWwindow* window);
    void RenderUI(goliaf::ecs::Registry& registry, std::string& scenePath);
    void Shutdown();
private:
    ImGuiIntegration imgui_;
    goliaf::ecs::Entity selected_ = 0;
};

}
