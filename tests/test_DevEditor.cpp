#include "dev/AssetPipeline.h"
#include "dev/editor/Editor.h"
#include "dev/level_editor/LevelEditor.h"
#include "dev/menu_editor/MenuEditor.h"

#include <gtest/gtest.h>

#include <algorithm>

TEST(DevEditorTest, DrawUiContainsPanelsAndData) {
    core_goliaf::dev::Editor editor;
    editor.initialize();

    editor.newLevelObject({1.0F, 2.0F, 3.0F});
    editor.newMenuButton("play", "Play", 40, 50);
    editor.queueAsset("textures/a.png");
    editor.updateFrame(144.0, 256.0);

    const auto ui = editor.drawUi();
    ASSERT_GE(ui.size(), 5U);

    EXPECT_NE(ui[0].find("FPS=144"), std::string::npos);
    EXPECT_NE(ui[1].find("Objects: 1"), std::string::npos);

    const auto hasAssetLine = std::any_of(ui.begin(), ui.end(), [](const std::string& line) {
        return line.find("[Assets] Queued: 1") != std::string::npos;
    });
    EXPECT_TRUE(hasAssetLine);
}

TEST(DevEditorTest, TogglePanelsHidesOutputLines) {
    core_goliaf::dev::Editor editor;
    editor.initialize();
    editor.toggleHierarchyPanel();
    editor.toggleInspectorPanel();
    editor.toggleAssetPanel();

    const auto ui = editor.drawUi();

    const auto hasHierarchy = std::any_of(ui.begin(), ui.end(), [](const std::string& line) {
        return line.find("[Hierarchy]") != std::string::npos;
    });
    const auto hasInspector = std::any_of(ui.begin(), ui.end(), [](const std::string& line) {
        return line.find("[Inspector]") != std::string::npos;
    });
    const auto hasAssets = std::any_of(ui.begin(), ui.end(), [](const std::string& line) {
        return line.find("[Assets]") != std::string::npos;
    });

    EXPECT_FALSE(hasHierarchy);
    EXPECT_FALSE(hasInspector);
    EXPECT_FALSE(hasAssets);
}

TEST(DevToolingTest, AssetPipelineBuildsArtifacts) {
    core_goliaf::dev::AssetPipeline pipeline;
    pipeline.initialize();
    pipeline.enqueue("textures/ui/button.png");
    pipeline.enqueue("models/player.glb");

    const auto artifacts = pipeline.build();
    ASSERT_EQ(artifacts.size(), 2U);
    EXPECT_EQ(artifacts[0], "packed/textures/ui/button.png.bin");
    EXPECT_EQ(artifacts[1], "packed/models/player.glb.bin");
}

TEST(DevToolingTest, MenuEditorRejectsDuplicateIdsAndSortsList) {
    core_goliaf::dev::MenuEditor menu;
    menu.initialize();

    EXPECT_TRUE(menu.addButton("z", "Z", 1, 1));
    EXPECT_TRUE(menu.addButton("a", "A", 2, 2));
    EXPECT_FALSE(menu.addButton("a", "A2", 3, 3));

    const auto buttons = menu.listButtons();
    ASSERT_EQ(buttons.size(), 2U);
    EXPECT_EQ(buttons[0].id, "a");
    EXPECT_EQ(buttons[1].id, "z");
}

TEST(DevToolingTest, LevelEditorCreateMoveDeleteObject) {
    core_goliaf::dev::LevelEditor level;
    level.initialize();

    const auto id = level.createObject({0.0F, 0.0F, 0.0F});
    EXPECT_EQ(level.objectCount(), 1U);

    EXPECT_TRUE(level.moveObject(id, {5.0F, 1.0F, -2.0F}));
    const auto obj = level.getObject(id);
    ASSERT_TRUE(obj.has_value());
    EXPECT_FLOAT_EQ(obj->position.x, 5.0F);

    EXPECT_TRUE(level.deleteObject(id));
    EXPECT_EQ(level.objectCount(), 0U);
}
