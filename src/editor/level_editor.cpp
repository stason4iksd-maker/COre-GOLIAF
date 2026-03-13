#include "editor/level_editor.hpp"
#include <imgui.h>

namespace editor {
void LevelEditor::draw() {
    ImGui::Begin("Scene Hierarchy");
    ImGui::Text("Root");
    ImGui::BulletText("Cube");
    ImGui::End();

    ImGui::Begin("Inspector");
    static float position[3] = {0.f, 0.f, 0.f};
    static float rotation[3] = {0.f, 0.f, 0.f};
    static float scale[3] = {1.f, 1.f, 1.f};
    ImGui::DragFloat3("Move", position, 0.05f);
    ImGui::DragFloat3("Rotate", rotation, 1.0f);
    ImGui::DragFloat3("Scale", scale, 0.05f);
    ImGui::End();

    ImGui::Begin("Asset Browser");
    ImGui::Text("models/cube.obj");
    ImGui::Text("textures/default.png");
    ImGui::Text("scripts/spin.lua");
    ImGui::End();
}
}
