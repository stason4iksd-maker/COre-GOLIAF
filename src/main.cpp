#include "AudioManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include <iostream>

int main() {
    goliaf::Renderer renderer;
    goliaf::AudioManager audio;
    auto& resources = goliaf::ResourceManager::instance();
    auto& input = goliaf::InputManager::instance();

    if (!renderer.init() || !audio.init()) {
        std::cerr << "Engine initialization failed\n";
        return 1;
    }

    goliaf::SceneManager sceneManager;
    auto& scene = sceneManager.createScene("TestScene");
    scene.addEntity().addComponent<goliaf::TransformComponent>(goliaf::Vec3{0.0F, 0.0F, 0.0F});

    resources.loadTexture("assets/textures/checker.png");
    resources.loadModel("assets/models/cube.obj");
    resources.loadSound("assets/audio/click.wav");

    bool running = true;
    int frames = 0;
    while (running && frames < 3) {
        input.processEvent({goliaf::Key::W, true});
        if (input.isPressed(goliaf::Key::Escape)) {
            running = false;
        }

        scene.update(1.0F / 60.0F);
        renderer.beginFrame();
        scene.render();
        renderer.endFrame();
        ++frames;
    }

    audio.shutdown();
    renderer.shutdown();
    resources.clear();
    return 0;
}
