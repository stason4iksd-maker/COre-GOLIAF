#include "editor/EditorApp.h"

#include <imgui.h>

#include "core/Logger.h"

namespace goliaf::editor {

bool EditorApp::Initialize(GLFWwindow* window) {
    if (!imgui_.Initialize(window)) return false;
    core::Logger::Log("Dev", "Editor started");
    core::Logger::Log("Dev", "UI initialized");
    return true;
}

void EditorApp::RenderUI(goliaf::ecs::Registry& registry, std::string& scenePath) {
    imgui_.BeginFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) { ImGui::MenuItem("Save"); ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Edit")) { ImGui::MenuItem("Undo"); ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Scene")) { ImGui::MenuItem("Load"); ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Build")) { ImGui::MenuItem("Build Player"); ImGui::EndMenu(); }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Hierarchy");
    for (const auto& e : registry.Entities()) {
        if (ImGui::Selectable(e.name.c_str(), selected_ == e.id)) selected_ = e.id;
    }
    ImGui::End();

    ImGui::Begin("Inspector");
    if (selected_ != 0) {
        if (auto* t = registry.GetTransform(selected_)) {
            ImGui::DragFloat3("Position", &t->x, 0.05f);
        }
    }
    ImGui::End();

    ImGui::Begin("Asset Browser");
    for (auto& entry : std::filesystem::recursive_directory_iterator("assets")) {
        ImGui::TextUnformatted(entry.path().string().c_str());
    }
    ImGui::Separator();
    ImGui::Text("Scene: %s", scenePath.c_str());
    ImGui::End();

    imgui_.EndFrame();
}

void EditorApp::Shutdown() { imgui_.Shutdown(); }

}
