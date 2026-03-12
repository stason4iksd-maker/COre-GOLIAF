#include "core/Application.h"
#include "core/Logger.h"
#include "scene/SceneLoader.h"

int main() {
    core_goliaf::core::Logger::info("Player", "Player build started");
    core_goliaf::core::Logger::info("Player", "Runtime initialized (stub).");

    core_goliaf::core::Application app;
    app.initialize("COre-GOLIAF Player", 1280, 720);

    core_goliaf::scene::SceneLoader loader;
    (void)loader.load("assets/level1.scene");

    app.run(2);
    app.shutdown();

    return 0;
}
