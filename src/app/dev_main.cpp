#include "assets/pipeline.hpp"
#include "editor/level_editor.hpp"
#include "editor/menu_editor.hpp"
#include "render/opengl_renderer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

int main() {
    render::OpenGLRenderer renderer;
    if (!renderer.init("Dev Editor")) return 1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    editor::MenuEditor menu;
    editor::LevelEditor level;
    assets::Pipeline pipeline;
    pipeline.importAssets("assets");
    pipeline.compileAndCache("build/cache");

    while (!renderer.shouldClose()) {
        renderer.beginFrame();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menu.draw();
        level.draw();

        ImGui::Begin("Viewport");
        ImGui::Text("3D viewport with cube + gizmos");
        ImGui::End();

        ImGui::Render();
        renderer.renderCube();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        renderer.endFrame();

        pipeline.shaderHotReload("shaders/default.glsl");
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    renderer.shutdown();
    return 0;
}
