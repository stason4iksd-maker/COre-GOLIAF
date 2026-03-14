#include "dev/editor/Editor.h"

#include <sstream>

namespace core_goliaf::dev {

void Editor::initialize() {
    levelEditor_.initialize();
    menuEditor_.initialize();
    assetPipeline_.initialize();
}

void Editor::toggleHierarchyPanel() {
    hierarchyPanel_ = !hierarchyPanel_;
}

void Editor::toggleInspectorPanel() {
    inspectorPanel_ = !inspectorPanel_;
}

void Editor::toggleAssetPanel() {
    assetPanel_ = !assetPanel_;
}

void Editor::newLevelObject(const goliaf::Vec3& position) {
    [[maybe_unused]] const auto id = levelEditor_.createObject(position);
}

void Editor::newMenuButton(const std::string& id, const std::string& title, int x, int y) {
    menuEditor_.addButton(id, title, x, y);
}

void Editor::queueAsset(const std::string& path) {
    assetPipeline_.enqueue(path);
}

void Editor::updateFrame(double fps, double memoryMb) {
    debugTools_.updateFrameStats(fps, memoryMb);
}

std::vector<std::string> Editor::drawUi() const {
    std::vector<std::string> lines;
    lines.push_back(debugTools_.buildOverlayText());

    if (hierarchyPanel_) {
        lines.push_back("[Hierarchy] Objects: " + std::to_string(levelEditor_.objectCount()));
    }
    if (inspectorPanel_) {
        lines.push_back("[Inspector] Selected: <none>");
    }
    if (assetPanel_) {
        lines.push_back("[Assets] Queued: " + std::to_string(assetPipeline_.build().size()));
    }

    const auto buttons = menuEditor_.listButtons();
    lines.push_back("[Menu] Buttons: " + std::to_string(buttons.size()));

    if (!buttons.empty()) {
        const auto& first = buttons.front();
        std::ostringstream oss;
        oss << "[Menu] FirstButton=" << first.id << " at (" << first.x << "," << first.y << ")";
        lines.push_back(oss.str());
    }

    return lines;
}

} // namespace core_goliaf::dev
