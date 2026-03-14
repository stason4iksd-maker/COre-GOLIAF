#pragma once

#include <string>
#include <vector>

#include "dev/AssetPipeline.h"
#include "dev/debug/DebugTools.h"
#include "dev/level_editor/LevelEditor.h"
#include "dev/menu_editor/MenuEditor.h"

namespace core_goliaf::dev {

class Editor {
public:
    void initialize();
    void toggleHierarchyPanel();
    void toggleInspectorPanel();
    void toggleAssetPanel();

    void newLevelObject(const goliaf::Vec3& position);
    void newMenuButton(const std::string& id, const std::string& title, int x, int y);
    void queueAsset(const std::string& path);

    void updateFrame(double fps, double memoryMb);
    [[nodiscard]] std::vector<std::string> drawUi() const;

private:
    bool hierarchyPanel_{true};
    bool inspectorPanel_{true};
    bool assetPanel_{true};

    LevelEditor levelEditor_;
    MenuEditor menuEditor_;
    AssetPipeline assetPipeline_;
    DebugTools debugTools_;
};

} // namespace core_goliaf::dev
