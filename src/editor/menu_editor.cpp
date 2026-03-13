#include "editor/menu_editor.hpp"
#include <imgui.h>

namespace editor {
void MenuEditor::draw() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New Scene");
            ImGui::MenuItem("Open Scene");
            ImGui::MenuItem("Save Scene");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {
            ImGui::MenuItem("Gizmo Move");
            ImGui::MenuItem("Gizmo Rotate");
            ImGui::MenuItem("Gizmo Scale");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
}
