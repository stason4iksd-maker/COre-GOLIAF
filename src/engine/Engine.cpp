#include "core/Engine.hpp"

#include "AudioManager.h"
#include "InputManager.h"
#include "PhysicsSystem.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

#include <iostream>
#include <vector>

namespace {
goliaf::Renderer g_renderer;
goliaf::AudioManager g_audio;
goliaf::SceneManager g_sceneManager;
goliaf::PhysicsSystem g_physics;
std::vector<goliaf::PhysicsBody> g_bodies;
}

bool Engine::initialize() {
    if (initialized_) {
        return true;
    }

    if (!g_renderer.init() || !g_audio.init()) {
        std::cerr << "[Engine] Failed to initialize subsystems" << std::endl;
        return false;
    }

    auto& scene = g_sceneManager.createScene("MainScene");
    auto& parent = scene.addEntity();
    auto& child = scene.addEntity();

    auto& parentTransform = parent.addComponent<goliaf::TransformComponent>(goliaf::Vec3{0.0F, 0.0F, 0.0F});
    auto& childTransform = child.addComponent<goliaf::TransformComponent>(goliaf::Vec3{1.0F, 0.0F, 0.0F});
    childTransform.setParent(&parentTransform);

    auto& resources = goliaf::ResourceManager::instance();
    resources.loadTexture("assets/textures/checker.png");
    resources.loadModel("assets/models/cube.obj");
    resources.loadSound("assets/audio/click.wav");

    g_bodies = {
        {{0.0F, 0.0F, 1.0F, 1.0F}, 1.0F, 0.2F, 0.0F},
        {{1.2F, 0.0F, 2.2F, 1.0F}, 1.0F, -0.2F, 0.0F},
    };

    initialized_ = true;
    running_ = true;
    frameCounter_ = 0;
    std::cout << "[Engine] Initialized" << std::endl;
    return true;
}

void Engine::update(double deltaTime) {
    if (!initialized_ || !running_) {
        return;
    }

    auto* scene = g_sceneManager.activeScene();
    if (scene != nullptr) {
        scene->update(static_cast<float>(deltaTime));
    }

    auto& input = goliaf::InputManager::instance();
    if (frameCounter_ == 3) {
        input.processEvent({goliaf::Key::Escape, true});
    }
    if (input.isPressed(goliaf::Key::Escape)) {
        requestStop();
    }

    g_physics.resolveCollisions(g_bodies, static_cast<float>(deltaTime));

    ++frameCounter_;
}

void Engine::render() {
    if (!initialized_ || !running_) {
        return;
    }

    g_renderer.beginFrame();
    if (auto* scene = g_sceneManager.activeScene(); scene != nullptr) {
        scene->render();
    }
    g_renderer.endFrame();
}

void Engine::shutdown() {
    if (!initialized_) {
        return;
    }

    goliaf::ResourceManager::instance().clear();
    goliaf::InputManager::instance().reset();
    g_audio.shutdown();
    g_renderer.shutdown();

    initialized_ = false;
    running_ = false;
    std::cout << "[Engine] Shutdown" << std::endl;
}

bool Engine::isRunning() const noexcept {
    return running_;
}

void Engine::requestStop() noexcept {
    running_ = false;
}
