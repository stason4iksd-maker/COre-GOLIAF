#include "core/Engine.hpp"
#include "dev/editor/Editor.h"

#include <iostream>

int main() {
    Engine engine;
    if (!engine.initialize()) {
        std::cerr << "[Dev] Engine initialization failed" << std::endl;
        return 1;
    }

    core_goliaf::dev::Editor editor;
    editor.initialize();
    editor.newLevelObject({0.0F, 0.0F, 0.0F});
    editor.newLevelObject({2.0F, 1.0F, 0.0F});
    editor.newMenuButton("start", "Start", 100, 200);
    editor.queueAsset("textures/checker.png");
    editor.queueAsset("models/cube.obj");

    int maxFrames = 10;
    while (engine.isRunning() && maxFrames-- > 0) {
        engine.update(1.0 / 60.0);
        engine.render();

        editor.updateFrame(60.0, 128.0 + static_cast<double>(10 - maxFrames));
        for (const auto& line : editor.drawUi()) {
            std::cout << line << '\n';
        }
    }

    engine.shutdown();
    std::cout << "[Dev] Completed run" << std::endl;
    return 0;
}
